# Exchange time

## Current Exchange Time

- Type: `Request`
- Message: `MessageType::ExchangeDataOnline::requestExchangeTime`
- Returns: `timestamp:TTimestamp`
- Params: `XString strExchange`

``` cpp tab="Send"
SendRequest<TTimestamp>(
  ExchangesData::MessageType::ExchangeDataOnline::requestExchangeTime::id(),
  "binance"
);
```

``` cpp tab="Register"
RegisterRequestCallback<TTimestamp, XString>(
  MessageType::ExchangeDataOnline::requestExchangeTime::id(),
   boost::bind(&method, this, _1)
);
```

## Diff exchange time vs local time

- Type: `Request`
- Message: `MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff`
- Returns: `timeoffset:TTimestamp`
- Params: `XString strExchange`

``` cpp tab="Send"
SendRequest<TTimestamp>(
  ExchangesData::MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff::id(),
  "binance"
);
```

``` cpp tab="Register"
RegisterRequestCallback<TTimestamp, XString>(
  MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff::id(),
  boost::bind(&method, this, _1)
);
```
