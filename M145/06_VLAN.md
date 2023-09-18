# Virtual Local Area Network
## Was ist ein VLAN
Ein VLAN (Virtual Local Area Network) ist ein logisches Netzwerk, das auf physischen Netzwerkinfrastrukturen wie Switches basiert. Es ermöglicht die Segmentierung eines physischen Netzwerks in mehrere virtuelle Netzwerke, wobei Geräte in einem VLAN so miteinander kommunizieren können, als wären sie direkt miteinander verbunden, unabhängig von ihrer physischen Standortierung im Netzwerk.

Die Hauptziele von VLANs sind die Verbesserung der Netzwerksicherheit, die Optimierung des Datenverkehrsmanagements und die Flexibilität bei der Verwaltung von Netzwerkkonfigurationen. Indem sie den Datenverkehr auf verschiedene VLANs aufteilen, können Unternehmen den Zugriff auf bestimmte Ressourcen beschränken, die Netzwerkleistung verbessern und die Netzwerkverwaltung vereinfachen. VLANs sind in großen Netzwerken, Rechenzentren und Unternehmensumgebungen weit verbreitet.

Die VLAN-Technologie unterscheidet dabei zwischen zwei Arten von Switchport:
- Accessport 
- Trunkport

Ein Accessport führt zu einem Endgerät (PC), der Trunkport zu einem anderen Switch oder einem Router.
Frames, welche über einen Trunkport verschickt werden, erhalten zusätzlich die VLAN-ID vorangestellt (1210 oder 1220 gemäss dem Beispiel oben). Diese Ethernetframes werden „taged“-Frames oder Dot1Q-Frames benannt. Ein „Tag“ ist ein „Label“; dem Frame wird eine Etikette mit der Vlan-ID angehängt.

Best Practise: Pro Subnetz ein VLAN

## Managed L2-Switch
