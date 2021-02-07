# Exchange Coins

## Request current symbol price

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestSymbolPrice`
- Returns: `double`
- Params: `XUuid uuidApiKey, stSymbolPair symbol`

``` cpp tab="Send"
SendRequest<double, XUuid,stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  "binance",
  stSymbolPair("btc","usdt")
);
```

``` cpp tab="Register"
RegisterRequestCallback<double, XUuid,stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
double method(const XUuid& uuidApiKey, const stSymbolPair& symbol)
{

}
```

## Request known pairs

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestKnownPairs`
- Returns: `symbols:TlstSymbolPairs`
- Params: `XUuid uuidApiKey`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, XUuid>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  "binance"
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, XUuid>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  boost::bind(&method, this, _1)
);
```


## Request market tickers with filter

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestFilteredMarketTickers`
- Returns: `symbols:TlstSymbolPairs`
- Params: `XUuid uuidApiKey, stSymbolsFilterAdvanced filter`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, XUuid,timeframe_t>(
  MessageType::ExchangeCoins::requestFilteredMarketTickers::id(),
  "binance",
  filter
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, XUuid,stSymbolsFilterAdvanced>(
  MessageType::ExchangeCoins::requestFilteredMarketTickers::id(),
  boost::bind(&method, this, _1, _2)
);
```

## Notification of new symbol

- Type: `Message`
- Message: `MessageType::ExchangeCoins::notifyExchangeNewSymbol`
- Params: `const stExchangeId& exchangeId, const stSymbolPair& symbol`

``` cpp tab="Send"
SendMessage<stExchangeId, stSymbolPair>(
  MessageType::ExchangeCoins::notifyExchangeNewSymbol::id(),
  boost::bind(&method, this, _1),
  exchange,
  symbol,
);
```

``` cpp tab="Register"
RegisterMessageCallback<stExchangeId, stSymbolPair>(
  MessageType::ExchangeCoins::notifyExchangeNewSymbol::id(),
  boost::bind(&method, this, _1, _2)
);
```

``` cpp tab="Handler"
void method(const stExchangeId& exchangeId, const Modules::Currencies::stSymbolPair& pair)
{

}
```

## Notification of exchange prices update

- Type: `Message`
- Message: `MessageType::ExchangeCoins::notifyExchangePriceUpdated`
- Params: `const stExchangeId& exchangeId, const stMarketTicker& tickUpdate`

``` cpp tab="Send"
SendMessage<stExchangeId, stMarketTicker>(
  MessageType::ExchangeCoins::notifyExchangePriceUpdated::id(),
  boost::bind(&method, this, _1),
  exchange,
);
```

``` cpp tab="Register"
RegisterMessageCallback<stExchangeId,stMarketTicker>(
  MessageType::ExchangeCoins::notifyExchangePriceUpdated::id(),
  boost::bind(&method, this, _1)
);
```

``` cpp tab="Handler"
void method(const stExchangeId& exchangeId, const stMarketTicker& tickUpdate)
{

}
```