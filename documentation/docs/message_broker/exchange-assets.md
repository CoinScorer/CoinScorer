# Exchange Assets

## Request asset state on account

- Type: `Request`
- Message: `MessageType::ExchangeAssets::requestGetAccountState`
- Returns: `stAccountState`
- Params: `XUuid apiKey, XString strAsset`

``` cpp tab="Send"
SendRequest<stAccountState, XUuid, XString>(
  MessageType::ExchangeAssets::requestGetAccountState::id(),
  apiKey,
  "BTC"
);
```

``` cpp tab="Register"
RegisterRequestCallback<stAccountState, XUuid, XString>(
  MessageType::ExchangeAssets::requestGetAccountState::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
stAccountState method(const XUuid& apiKey, const XString& strAsset)
{

}
```

## Notification of asset change on API account

- Type: `Message`
- Message: `MessageType::ExchangeAssets::notifyAccountAssetChanged`
- Params: `XString strApiKey, const stAccountState& accountState`

``` cpp tab="Send"
SendMessage<XString, stAccountState>(
  MessageType::ExchangeAssets::notifyAccountAssetChanged`::id(),
  strApiKey,
  accountState,
);
```

``` cpp tab="Register"
RegisterMessageCallback<XString, stAccountState>(
  MessageType::ExchangeAssets::notifyAccountAssetChanged`::id(),
  boost::bind(&method, this, _1, _2)
);
```

``` cpp tab="Handler"
void method(const XString& strApiKey, const Modules::Currencies::stAccountState& accountState)
{

}
```
