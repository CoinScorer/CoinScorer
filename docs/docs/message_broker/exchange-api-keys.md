# Exchange Api Keys

## Notification of API key change

- Type: `Message`
- Message: `MessageType::ExchangeApiKeys::notifyApiKeyEvent`
- Params: `const XUuid& uuidApiKey, EnmApiKeyAction action`

``` cpp tab="Send"
SendMessage<XString, stAccountState>(
  MessageType::ExchangeApiKeys::notifyApiKeyEvent`::id(),
  uuidApiKey,
  action,
);
```

``` cpp tab="Register"
RegisterMessageCallback<XString, stAccountState>(
  MessageType::ExchangeApiKeys::notifyApiKeyEvent`::id(),
  boost::bind(&method, this, _1, _2)
);
```

``` cpp tab="Handler"
void method(const XUuid& uuidApiKey, EnmApiKeyAction action)
{

}
```
