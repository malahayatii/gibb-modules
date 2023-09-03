# bind9 als DNS server konfigurieren
## bind9 installieren
```bash
sudo apt install bind9
```
## Konfiguration
Unter /etc/bind wurden folgende Dateien erstellt:
```
named.conf
named.conf.default-zones
named.conf.local
named.conf.options
```

Für die Smartlearnumgebung wurden folgende Einstellungen in named.conf.options gemacht
```yaml
options{
    directory "/var/cache/bind";

    forwarders {
        1.1.1.1;
        9.9.9.9;
    };
    
    dnssec-validation auto;

    //IPv4
    listen-on port 53 {
        any;
    };

    allow-query {
        any;
    };

    allow-recursion {
        any;
    };

    listen-on-v6 { none; };
};
```

## Clients mit LS1 als DNS konfigurieren
WP1 wird im GUI konfiguriert.
LP1 wird auch im GUI konfiguriert.
LS1 kann nur per /etc/netplan konfiguriert werden.
Folgender Eintrag:
```yaml
network:
  version: 2
  renderer: networkd
  ethernets:
    eth0:
      addresses: [ 192.168.120.61/24 ]
      dhcp4: false
      routes:
        - to: default
          via: 192.168.120.2
      nameservers:
        addresses: [ 192.168.120.61 ]
        search: [ smartlearn.dmz ]
```

Damit die Änderung übernommen wird muss folgender Befehl noch ausgeführt werden
```bash
sudo netplan apply
```

## Fehlersuche
Fehler in der Konfiguration gibt Bind im Log aus, diese findet man unter /var/log/syslog

## Kommentare
Kommentare in der Konfigurationsdatei starten jeweils mit "//"

## Liste der Root-Server aktualisieren
Um eine aktuelle Liste der Root-Server unter db.root zu speichern, fragen wir einen Root-Server an
```bash
su

dig @a.root-servers.net | grep -E -v ';|^$' > /etc/bind/db.root
``` 

# DNS-Zonen einrichten
## Netwerküberssicht
![Alt text](image.png)

## Zonendatei für die DMZ
# DMZ-Zone dmz.mattefit.ch
```yaml
;
; Zonendatei für dmz.mattefit.ch.
; /etc/bind/db.ch.mattefit.dmz
;
$TTL    3600
@       IN      SOA     vmls1.dmz.mattefit.ch.      root.mattefit.ch. (
                         1
                        1H
                        2H
                        1D
                        1H )

@       IN      NS      vmls1.dmz.mattefit.ch.
vmlf1   IN      A       192.168.220.1
vmls1   IN      A       192.168.220.10
```
```yaml
;
; Zonendatei für 220.168.192.in-addr.arpa.
; /etc/bind/db.192.168.220
;
$TTL    3600
@       IN      SOA     vmls1.dmz.mattefit.ch.      root.mattefit.ch. (
                         1
                        1H
                        2H
                        1D
                        1H )

@       IN      NS      vmls1.dmz.mattefit.ch.
1       IN      PTR     vmlf1.dmz.mattefit.ch.
10      IN      PTR     vmls1.dmz.mattefit.ch.
```
Damit die Zonen von unserem Bind gelesen werden müssen folgende Einträge in /etc/bind/named.conf.local
gemacht werden
```yaml
//
// DMZ
//
zone "dmz.mattefit.ch" {
        type master;
        notify no;
        file "/etc/bind/db.ch.mattefit.dmz";
};
zone "220.168.192.in-addr.arpa" {
        type master;
        notify no;
        file "/etc/bind/db.192.168.220";
};
```