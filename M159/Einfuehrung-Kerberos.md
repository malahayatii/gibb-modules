# Kerberos
Die 3 Köpfe stehen für die 3 Elemente Authentisierung
- Client
- Server
- Key Distribution Center (KDC)
## Directory Services
### X-500-Spezifikation
Standard des globalen Verzeichnisdienstes, die ADDS (Active Directory Domain Services)von Microsoft und SAMBA basieren darauf.
Zugriff auf die Objekte in der X-500 basierten DB erfolgt mit LDAP (Lightweight Directory Access Protocol).
Abfragen der Server untereinander erfolgt auch mit LDAP

### Authentifizierungsprotokoll Shritt für Shritt
1. User meldet sich an seinem Arbeitsgerät mit Username und Passwort an
2. Kerberos authentifiziert den Benutzer und stellt über das Key Distribution Center (KDC) ein Ticket aus
3. Das Ticket, welches TGT (Ticket Granting Ticket) dient als Identitätsnachweise der Benutzer
4. Das KDC stellt weiter Tickets aus (Session Tickets) für die wieteren Aktivitäten des Benutzers

## Netzwerkauthentifizierung mit Kerberos
Definition der Begriffe
- Authentisierung: Nachweis der eigenen Identität
- Authentifizierung: Überprüfung der Identität

Netzwekprotokolle zur Authentisierung
- Webserver -> http
- Email -> SMTP, POP3, IMAP
- Fileservices -> CIFS, NFS, AFS, etc.
- Printservices -> IPP
- Active Directory Services -> LDAP
- Host-Server -> SSH; etc.

Es sind immer 2 Teilnehmer benötigt. Teilnehmer A der sich authentisieren will und Teilnehmer B der Teilnehmer A authentifizieren möchte.
Die Teilnehmer können sein:
- A: Anwender, B: Service
- A: Anwender, B: Anwender
- A: Service, B: Service

## Elemente
### KDC
Das Key Distribution Center vermittelt die Authentisierung zwischen Client und Netzwerkdiensten. Alle Clients und Services haben ein 
Vertrauensverhältnis (Trust) zum KDC.

![Kerberos Authentisierung](/M159/images/Kerberos-Authentisierung.png)
