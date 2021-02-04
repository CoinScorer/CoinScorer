# Architecture

Components:

## Exchange online data

Realtime data from exchanges

## Exchange history data

History data from exchanges

## Exchange cache

Cached historic data from exchanges stored in local storage. Also caching latest candle price.

## Exchange candle splitter (concept only)

Instead of downloading several timeframes from exchange, allow download only one stream and split it to several timeframes on local side.

## Indicators

Realtime calculated indicators from exchange streams.
