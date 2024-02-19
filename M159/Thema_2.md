# Setup ADDS mit Samba im Smartlearn Labor

| Server/Client Name | IP | Rolle |
|--------------------|----|-------|
| vmLS1 | 192.168.110.61 | Domain Controller | 
| vmLS2 | 192.168.110.62 | Domain Member Server |

# Installation und Konfiguration vmLS1
Als erstes wird die Search-Zone von LS1 unter `/etc/netplan/00-eth0.yaml` folgendermassen angepasst:
![alt text](images/00-eth0.yaml.png)
Damit der Domain Controller sich selber nach Namen kennt, wird der hostname in `/etc/hosts` eingetragen:
![alt text](images/etc-hosts.png)
Anschliessend wird der Hostnamen in /etc/hostname angepasst:
![alt text](images/hostname.png)
Repositories und Packete aktualisieren, danach das Gerät Neustarten:
```bash
sudo apt update && sudo apt upgrade -y && sudo snap refresh -y && sudo reboot
```
## Samba installieren
```bash
sudo apt install samba smbclient heimdal-clients
```
Während der Installtion sollte es nach folgenden Informationen fragen:
- Kerberos Realm: SAM159.IET-GIBB.CH
- FQDN: vmLS1.sam159.iet-gibb.ch
Weitere Abhängikeiten installieren:
```bash
sudo apt install acl attr build-essential libacl1-dev libattr1-dev \
    libblkid-dev libgnutls28-dev libreadline-dev python2-dev python2 \
    python-dev-is-python3 python3-dnspython gdb pkg-config libpopt-dev \
    libldap2-dev libbsd-dev krb5-user docbook-xsl libcups2-dev ntp \
    ntpdate net-tools git winbind libpam0g-dev dnsutils lsof
```
Ein Backup vom samba-conf Datei erstellen:
```bash
mv /etc/samba/smb.conf /etc/samba/smb.conf.orig
```
## Samba als KCD für das Realm SAM159.IET-GiBB.CH einrichten
```bash
samba-tool domain provision
```
Die folgenden Eingaben eintragen
![alt text](images/samba-tool.png)
Dies reultiert in folgender Konfigurations-Datei
![alt text](images/smbconf.png)

Da das DNS Dienst von samba zu Verfügung gestellt wird müssen wir das DNS-resolving ausschalten
```bash
sudo systemctl disable systemd-resolved && sudo systemctl stop systemd-resolved
sudo cp /etc/resolv.conf resolv.conf.backup
sudo rm /etc/resolv.conf
```
Danach ein eigenes resolv.conf erstellen mit folgenden Eintrag:
```bash
nameserver 192.168.110.61
search sam159.iet-gibb.ch
```
Samba systemd-service starten
```bash
sudo systemctl unmask samba-ad-dc
sudo systemctl enable samba-ad-dc
sudo systemctl start samba-ad-dc
```
Aber dies resultiert in ein Fehler da der Service nicht exisitiert. Ich erstelle ihn selbst unter /etc/systemd/system/samba-ad-cd.service folgendermassen:
![alt text](images/samba-ad-dc.png)

Danach die vorherigen Befehle nochmals ausführen.

Samba konfigurieren für die Benutzung des Kerberos-Authentifizierungsdienst unter /etc/krb5.conf
![alt text](images/krb5.conf.png)

Netzwerk testen
```bash
sudo systemctl start systemd-resolved
sudo resolvectl status
```
![alt text](images/resolvectl.png)
und systemd-resolve wieder ausschalten:
```bash
sudo systemctl stop systemd-resolved
```
DNS-Service von samba aktualisieren
```bash
samba_dnsupdate --verbose
```
Reverse Lookup-Zone per samba-tool einrichten:
```bash
# Zone kreieren
sudo samba-tool dns zonecreate vmLS1 110.168.192.in-addr.arpa -Uadministrator
# Reverse Lookup Zone einrichten
sudo samba-tool dns add 192.168.110.61 110.168.192.in-addr.arpa 61 PTR vmls1.sam159.iet-gibb.ch -Uadministrator
```