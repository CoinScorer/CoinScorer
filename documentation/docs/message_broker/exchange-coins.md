# Exchange Coins

## Request current symbol price

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestSymbolPrice`
- Returns: `Atomix::TimestampValue<double>`
- Params: `stExchangeId exchangeId, stSymbolPair symbol`

``` cpp tab="Send"
SendRequest<Atomix::TimestampValue<double>, stExchangeId,stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  "binance",
  stSymbolPair("btc","usdt")
);
```

``` cpp tab="Register"
RegisterRequestCallback<Atomix::TimestampValue<double>, stExchangeId, stSymbolPair>(
  MessageType::ExchangeCoins::requestSymbolPrice::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
Atomix::TimestampValue<double> method(const stExchangeId& exchangeId, const stSymbolPair& symbol)
{

}
```

## Request known pairs

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestKnownPairs`
- Returns: `symbols:TlstSymbolPairs`
- Params: `stExchangeId exchangeId`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, stExchangeId>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  "binance"
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, stExchangeId>(
  MessageType::ExchangeCoins::requestKnownPairs::id(),
  boost::bind(&method, this, _1)
);
```


## Request market tickers with filter

- Type: `Request`
- Message: `MessageType::ExchangeCoins::requestFilteredMarketTickers`
- Returns: `symbols:TlstSymbolPairs`
- Params: `stExchangeId exchangeId, stSymbolsFilterAdvanced filter`

``` cpp tab="Send"
SendRequest<TlstSymbolPairs, stExchangeId,timeframe_t>(
  MessageType::ExchangeCoins::requestFilteredMarketTickers::id(),
  "binance",
  filter
);
```

``` cpp tab="Register"
RegisterRequestCallback<TlstSymbolPairs, stExchangeId,stSymbolsFilterAdvanced>(
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