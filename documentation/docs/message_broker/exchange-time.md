# Exchange time

## Current Exchange Time

- Type: `Request`
- Message: `MessageType::ExchangeDataOnline::requestExchangeTime`
- Returns: `timestamp:TTimestamp`
- Params: `stExchangeId exchangeId`

``` cpp tab="Send"
SendRequest<TTimestamp>(
  ExchangesData::MessageType::ExchangeDataOnline::requestExchangeTime::id(),
  stExchangeId("binance")
);
```

``` cpp tab="Register"
RegisterRequestCallback<TTimestamp, stExchangeId>(
  MessageType::ExchangeDataOnline::requestExchangeTime::id(),
   boost::bind(&method, this, _1)
);
```

## Diff exchange time vs local time

- Type: `Request`
- Message: `MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff`
- Returns: `timeoffset:TTimestamp`
- Params: `stExchangeId exchangeId`

``` cpp tab="Send"
SendRequest<TTimestamp>(
  ExchangesData::MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff::id(),
  stExchangeId("binance")
);
```

``` cpp tab="Register"
RegisterRequestCallback<TTimestamp, stExchangeId>(
  MessageType::ExchangeDataOnline::requestExchangeVsLocalTimeDiff::id(),
  boost::bind(&method, this, _1)
);
```
