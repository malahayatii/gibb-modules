### Accessing the WebUI from WAN
Method 1 Create Firwall Rules:
1. In Interfaces disable Block private Networks and loopback address
2. Add Firwall Rules:   
                Action: pass
                Interface: WAN
                Address Family: Ipv4
                Protocol: TCP
3. Set source settings to "any"
4. Set destination settings to: 
                Destination: WAN Address
                Destination port range: HTTP (Or the custom port)

Method 2 Disable the packet filter (breaks the firewall)
1. enter ```pfctl -d``` to disable the packet filter
2. enter ```pfctl -e``` to enable the packet filter