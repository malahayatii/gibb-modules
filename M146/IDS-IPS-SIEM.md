## Wazuh
Install wazuh agent, server and dashboard
```bash
curl -sO https://packages.wazuh.com/4.7/wazuh-install.sh && sudo bash ./wazuh-install.sh -a
```
Important output
    URL: https://<wazuh-dashboard-ip>:443
    User: admin
    Password: cezr?SFAl4Xgx32kYOn.RV7yZ82y7?iD

Troubleshoot https://<wazuh-dashboard-ip>:443 unreachable
When trying to access the dashboard using the IP-address of the wazuhvm:443 an error occurs. Without entering port 443 use the VM's IP-address as the webaddress

### Deploy Agent for LP1
Select Package DEB amd64, then enter the IP-address of LP1 which is 192.168.110.31. Wazuh will generate installation commands for the target. Copy and paste them to the target machine.

Install the wazuh agent
```bash
wget https://packages.wazuh.com/4.x/apt/pool/main/w/wazuh-agent/wazuh-agent_4.7.1-1_amd64.deb && sudo WAZUH_MANAGER='192.168.110.32' dpkg -i ./wazuh-agent_4.7.1-1_amd64.deb
```

Start the agent
```bash
sudo systemctl daemon-reload
sudo systemctl enable wazuh-agent
sudo systemctl start wazuh-agent
```
Troubleshoot "wazuh-agent.service has entered the 'failed' state with result 'exit-code'

The actual logs of wazuh are saved under /var/ossec/logs/ossec.log. Check them as follows:
```bash
cat /var/ossec/logs/ossec.log
# Resulting log
Invalid server address found: 'MANAGER_IP'
```
This can be adjusted in the config file under /var/ossec/etc/ossec.conf


