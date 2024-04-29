# Setup

## Update Ubuntu VMs

for vmls3, 4 and 5

```shell
sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y
```

restart if needed 

```shell
sudo reboot now
```

## setting up vmls3 as DNS server

### install bind9 and dnsutils

```shell
sudo apt install bind9 dnsutils -y
```

configure the DNS server

```shell
.
├── named.conf                  # points to the other confs
├── named.conf.default-zones    # localhost, etc
├── named.conf.local            # zones you configure
└── named.conf.options          # global DNS options
```

### configure local zones in `/etc/bind/named.conf.local`

```conf
zone "smartlearn.lan" in {
    type master;
    file "/etc/bind/db.smartlearn.lan";
};

zone "210.168.192.in-addr.arpa" in {
    type master;
    file "/etc/bind/db.192.168.210";
};

zone "smartlearn.dmz" in {
    type master;
    file "/etc/bind/db.smartlearn.dmz";
};

zone "220.168.192.in-addr.arpa" in {
    type master;
    file "/etc/bind/db.192.168.220";
};
```

### configure the individual db files

`/etc/bind/db.smartlearn.lan`

```conf
$ORIGIN smartlearn.lan.
    $TTL    604800
    @       IN      SOA     vmls3.smartlearn.dmz.
vmadmin.vmls3.smartlearn.dmz. (
    2020051604      ; Serial
    604800          ; Refresh
    86400           ; Retry
    2419200         ; Expire
    604800 )        ; Negative Cache TTL
    ;
    ;
    ; Name Servers
    ;
    ;@      IN      NS      ns.smartlearn.dmz.
    smartlearn.lan. IN      NS      vmls3.smartlearn.dmz.  ; vmls3 is a nameserver for smartlearn.lan
    ;
    ; Host addresses
    ;
    @       IN      AAAA    ::1
    vmls3   IN      A       192.168.220.12
    vmlf1   IN      A       192.168.210.1
    vmwp1   IN      A       192.168.210.10
    vmlp1   IN      A       192.168.210.30
    vmls4   IN      A       192.168.210.60
    vmls5   IN      A       192.168.210.61
    ;
    ; Aliases
    ;
    www     IN      CNAME       vmls5.smartlearn.lan.
;www.smartlearn.lan is an alias for vmls3.smartlearn.lan
    ftp     IN      CNAME       vmls5.smartlearn.lan.
;ftp.smartlearn.lan is an alias for vmls3.smartlearn.lan
    ns      IN      CNAME       vmls3.smartlearn.dmz.
;ns.smartlearn.dmz is an alias for vmls3.smartlearn.dmz
```

`db.192.168.210`

```conf
;
; BIND reverse data file for local loopback interface
;
$TTL    604800
@       IN      SOA     ns.smartlearn.dmz.      vmadmin.smartlearn.dmz. (
                        2024042801  ;Serial
                        604800      ; Refresh
                        86400       ; Retry
                        2419200     ; Expire
                        604800 )    ; Negative Cache TTL
;
@       IN      NS      ns.smartlearn.dmz.
10      IN      PTR     vmwp1.smartlearn.lan.
30      IN      PTR     vmlp1.smartlearn.lan.
60      IN      PTR     vmls4.smartlearn.lan.
61      IN      PTR     vmls5.smartlearn.lan.
61      IN      PTR     www.smartlearn.lan.
61      IN      PTR     ftp.smartlearn.lan.
1       IN      PTR     vmlf1.smartlearn.lan.
```

`db.smartlearn.dmz`

```conf
$ORIGIN smartlearn.dmz.
    $TTL    604800
    @       IN      SOA     vmls3.smartlearn.dmz.
vmadmin.vmls3.smartlearn.dmz. (
    2020051604      ; Serial
    604800          ; Refresh
    86400           ; Retry
    2419200         ; Expire
    604800 )        ; Negative Cache TTL
    ;
    ;
    ; Name Servers
    ;
    ;@      IN      NS      ns.smartlearn.dmz.
    smartlearn.dmz. IN      NS      vmls3.smartlearn.dmz.  ; vmls3 is a nameserver for smartlearn.lan
    ;
    ; Host addresses
    ;
    @       IN      AAAA    ::1
    vmls3   IN      A       192.168.220.12
    vmlf1   IN      A       192.168.210.1
    vmwp1   IN      A       192.168.210.10
    vmlp1   IN      A       192.168.210.30
    vmls4   IN      A       192.168.210.60
    vmls5   IN      A       192.168.210.61
    ;
    ; Aliases
    ;
    www     IN      CNAME       vmls5.smartlearn.lan.
;www.smartlearn.lan is an alias for vmls3.smartlearn.lan
    ftp     IN      CNAME       vmls5.smartlearn.lan.
;ftp.smartlearn.lan is an alias for vmls3.smartlearn.lan
    ns      IN      CNAME       vmls3.smartlearn.dmz.
;ns.smartlearn.dmz is an alias for vmls3.smartlearn.dmz 
```

`/etc/bind/db.192.168.220`

```conf
;
; BIND reverse data file for local loopback interface
;
$TTL    604800
@       IN      SOA     ns.smartlearn.dmz.      vmadmin.smartlearn.dmz. (
                        2024042801  ;Serial
                        604800      ; Refresh
                        86400       ; Retry
                        2419200     ; Expire
                        604800 )    ; Negative Cache TTL
;
@       IN      NS      ns.smartlearn.dmz.
12      IN      PTR     ns.smartlearn.dmz.
12      IN      PTR     www.smartlearn.dmz.
12      IN      PTR     ftp.smartlearn.dmz.
12      IN      PTR     vmls3.smartlearn.dmz.
1       IN      PTR     vmlf1.smartlearn.dmz.
```

### Forward DNS Server

`/etc/bind/named.conf.options`
