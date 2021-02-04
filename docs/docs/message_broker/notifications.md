# Notification

## Send user notification

- Type: `Message`
- Message: `MessageType::Notifications::userNotification`
- Params: `XNotification ptrNotification, XNotificationData ptrData`

``` cpp tab="Send"
SendMessage<XNotification,XNotificationData>(
  MessageType::Notifications::userNotification::id(), 
  ptrNotification, 
  ptrData
);
```

``` cpp tab="Register"  
RegisterMessageCallback<XNotification, XNotificationData>(
  MessageType::Notifications::userNotification::id(), 
  boost::bind(&method, this, _1, _2)
);
```
