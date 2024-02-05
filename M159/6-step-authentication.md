# 6 step Kerberos Authentication

## 1. Authentication Request (AS-REQ)
- Client to Authentication Server (AS):
  -  The client sends an Authentication Service Request to the AS. The request includes the clients identity (usually username)
  **Encrypted with**: The request is encrypted with the user's secret key or a password hash
- **AS decrypts**: Knows the key the client used and uses it to decrypt the message

## 2. Authentication Service Reply (AS-REP):
- AS to Client:
  - If the clients Identity is valid (knows the principle) the AS issues the Ticket Granting Ticket (TGT)
    **Encrypted with**: The TGT is encrypted with the clients secret key or a key derived from the clients password

## 3. Ticket Granting Service Request (TGS-REQ)
- Client sends a request to the Ticket Granting Server
  - The request contains the TGT and demands access to a specific service and the clients authenticator
    **Encrypted with**: The request is encrypted with the session key contained in the TGT
- **TGS decrypts**: The request is decrypted using the TGT's session key to verify the clients identity

## 4. Ticket Granting Service Reply (TGS-REP)
- TGS to Client:
  - Opens the requst and decrypts it with the session key and reads the authenticator verifying the client. Then replies with a Service Ticket
    **Encrypted with**: The Service Ticket is encrypted with the services secret key which in turn is encrypted with the session key

## 5. Application Service Request (AP-REQ)
- Client to Service:
  - The request contains the service ticket and authenticator
- **AP decrypts**: The service decrypts the Service Ticket using it's secret key to verify it, can read server session key and username

## 6. Application Service Reply (AP-REP)
- Service to Client:
  - Decrypts Service Ticket and gets service session key, Confirms clients identity and authorises access
