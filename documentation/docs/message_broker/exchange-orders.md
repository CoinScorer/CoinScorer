# Exchange Orders

## Create new order

- Type: `Demand`
- Message: `MessageType::ExchangeOrders::demandCreateOrder`
- Returns: `stExchangeOrder`
- Params: `const XUuid& apiKey, const stExchangeOrderCreate& order`

``` cpp tab="Send"
SendDirectDemand<stExchangeOrder,XUuid, stExchangeOrderCreate>(
  MessageType::ExchangeOrders::demandCreateOrder::id(),
  apiKey,
  stExchangeOrderCreate()
);
```

``` cpp tab="Register"
RegisterDemandCallback<stExchangeOrder,XUuid, stExchangeOrderCreate>(
  MessageType::ExchangeOrders::demandCreateOrder::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
stExchangeOrder method(const XUuid& apiKey, const stExchangeOrderCreate& order)
{

}
```

## Cancel order

- Type: `Demand`
- Message: `MessageType::ExchangeOrders::demandCancelOrder`
- Returns: `stExchangeOrder`
- Params: `const XUuid& apiKey, const stExchangeOrderId& orderId`

``` cpp tab="Send"
SendDirectDemand<stExchangeOrder, XUuid, stExchangeOrderId>(
  MessageType::ExchangeOrders::demandCancelOrder::id(),
  apiKey,
  stExchangeOrderId()
);
```

``` cpp tab="Register"
RegisterDemandCallback<stExchangeOrder, XUuid, stExchangeOrderId>(
  MessageType::ExchangeOrders::demandCancelOrder::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
stExchangeOrder method(const XUuid& apiKey, const stExchangeOrderId& orderId)
{

}
```

## Cancel all orders

- Type: `Demand`
- Message: `MessageType::ExchangeOrders::demandCancelAllOrders`
- Returns: `stExchangeOrdersContainer`
- Params: `const XUuid& apiKey, const stSymbolPair& symbol`

``` cpp tab="Send"
SendDirectDemand<stExchangeOrdersContainer, XUuid, stSymbolPair>(
  MessageType::ExchangeOrders::demandCancelAllOrders::id(),
  apiKey,
  symbol
);
```

``` cpp tab="Register"
RegisterDemandCallback<stExchangeOrdersContainer, XUuid, stSymbolPair>(
  MessageType::ExchangeOrders::demandCancelAllOrders::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
stExchangeOrdersContainer method(const XUuid& apiKey, const stSymbolPair& symbol)
{

}
```

## Request order info

- Type: `Request`
- Message: `MessageType::ExchangeOrders::requestGetOrder`
- Returns: `stExchangeOrder`
- Params: `const XUuid& apiKey, const stExchangeOrderId& orderId`

``` cpp tab="Send"
SendRequest<stExchangeOrder, XUuid, stExchangeOrderId>(
  MessageType::ExchangeOrders::requestGetOrder::id(),
  apiKey,
  orderId
);
```

``` cpp tab="Register"
RegisterRequestCallback<stExchangeOrder, XUuid, stExchangeOrderId>(
  MessageType::ExchangeOrders::requestGetOrder::id(),
  boost::bind(&method, this, _1,_2)
);
```

``` cpp tab="Handler"
stExchangeOrder method(const XUuid& apiKey, const stExchangeOrderId& orderId)
{

}
```


## Notification of orcer change

- Type: `Message`
- Message: `MessageType::ExchangeCoins::notifyOrderChanged`
- Params: `const XUuid& uuidApiKey, const stExchangeOrderExecution& order`

``` cpp tab="Send"
SendMessage<XUuid, stExchangeOrderExecution>(
  MessageType::ExchangeCoins::notifyOrderChanged::id(),
  boost::bind(&method, this, _1),
  strApiKey,
  order,
);
```

``` cpp tab="Register"
RegisterMessageCallback<XUuid, stExchangeOrderExecution>(
  MessageType::ExchangeCoins::notifyOrderChanged::id(),
  boost::bind(&method, this, _1, _2)
);
```

``` cpp tab="Handler"
void method(const XUuid& uuidApiKey, const stExchangeOrderExecution& order)
{

}
```
