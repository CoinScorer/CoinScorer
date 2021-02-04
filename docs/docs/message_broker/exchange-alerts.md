# Exchange Alerts

## Alert notification

- Type: `Message`
- Message: `MessageType::ExchangeAlerts::onNotify(uuid)`
- Params: `timestamp_t timestamp`

``` cpp tab="Send"
SendMessage(MessageType::ExchangeAlerts::onNotify(uuidAlert), tmTimestamp);
```

``` cpp tab="Register"
RegisterMessageCallback<timestamp_t>(
    MessageType::ExchangeAlerts::onNotify(uuid),
    boost::bind(&method, this, _1)
);
```

``` cpp tab="Handler"
void method(timestamp_t tmTimestamp)
{

}
```
