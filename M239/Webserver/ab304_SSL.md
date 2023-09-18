### Create and sign certificate
Zertifikat und Keyfile erstellen (optionen verbose abarbeiten)
```bash
sudo openssl req -new -newkey rsa:2048 -nodes -keyout ch.mattefit.staff.admin.csr -sha256
```

Manuell Zertifikat austellen
```bash
sudo openssl x509 -req -days 365 -in ch.mattefit.staff.admin.csr -signkey ch.mattefit.staff.admin.key -out ch.mattefit.staff.admin.crt -sha256
```

### Neuer VirtualHost kreieren mit SSLEngine
ssl aktivieren
```bash
sudo a2enmod ssl
```

neuer file /etc/apache2/sites-available/ch.mattefit.admin_ssl.conf

```html
<VirtualHost *:443
ServerName vmls1
ServerAlias admin.staff.mattefit.ch
ServerAdmin hostmaster@mattefit.ch
DocumentRoot /srv/www/ch.mattefit.staff.admin/htdocs/

# SSL
SSLEngine on
SSLCertificateFile /home/vmadmin/ch.mattefit.staff.admin.crt
SSLCertificateKeyFile /home/vmadmin/ch.mattefit.staff.admin.key

# Logs
ErrorLog /var/log/apache2/1slmv_error.log
CustomLog /var/log/apache2/1slmv_access.log
combined
# Directoires
<Directory /srv/www/ch.mattefit.staff.admin/htdocs>
Require all granted
</Directory>
<Directory /srv/www/ch.mattefit.staff.admin/htdocs>
    AuthType Basic
    AuthName "Restricted Area"
    AuthUserFile /srv/www/ch.mattefit.staff.admin/.htpasswd
    Require valid-user
</Directory>
</VirtualHost>
```
alte Seite deaktivieren und neue aktivieren
```bash
sudo a2dissite ch.mattefit.admin.conf
sudo a2enmode ch.mattefit.admin_ssl.conf
```
apache2 neustarten
```bash
sudo systemctl restart apache2
```

