#pragma once


struct stLpConfiguration
{
	double dbAmountLp{ 0 };

	double dbPriceToken1{ NULLDOUBLE };
	double dbPriceToken2{ NULLDOUBLE };

	double dbAmountToken1{ NULLDOUBLE };
	double dbAmountToken2{ NULLDOUBLE };


	double GetLpValue() const { return dbPriceToken1 * dbAmountToken1 + dbPriceToken2 * dbAmountToken2; }
	double GetTotalValue() const { return GetLpValue() * dbAmountLp; }
	void SetAmountByLpPairPrice(double dbLpPrice)
	{
		XASSERT(dbPriceToken1 != NULLDOUBLE && dbPriceToken2 != NULLDOUBLE);
		dbAmountToken1 = (dbLpPrice / 2.0) / dbPriceToken1;
		dbAmountToken2 = (dbLpPrice / 2.0) / dbPriceToken2;
	}

	XString GetDebugOutput()
	{
		return XString::FromFormat("$%.6f * %.6f + $%.6f * %.6f = $%.6f", dbPriceToken1, dbAmountToken1, dbPriceToken2, dbAmountToken2, GetLpValue());
	}
};

struct stStakeConfiguration
{
	double dbPriceToken{ NULLDOUBLE };
	double dbAmountToken{ 0 };
	double GetTotalValue() const { return dbPriceToken * dbAmountToken; }

	XString GetDebugOutput()
	{
		return XString::FromFormat("$%.6f * %.6f = $%.6f", dbPriceToken, dbAmountToken, GetTotalValue());
	}
};

struct stRewardWallet
{
	double dbRewardAmount{ 0 };
	double dbLastPrice{ 0 };
	double GetTotalValue() const { return dbLastPrice * dbRewardAmount; }

	XString GetDebugOutput()
	{
		return XString::FromFormat("$%.6f * %.6f = $%.6f", dbLastPrice, dbRewardAmount, GetTotalValue());
	}
};

struct stStepConfiguration 
{
	double dbPriceChangeToken1{0}; //price change by percent for token1
	double dbPriceChangeToken2{0}; //price change by percent for token2
	timeframe_t tfStepLength{ timeframe_enum::Day1 };

	void SetPriceChangeToken1Percent(double dbPercent) { dbPriceChangeToken1 = dbPercent / 100.0; }
	void SetPriceChangeToken2Percent(double dbPercent) { dbPriceChangeToken2 = dbPercent / 100.0; }
};

struct stRewardsConfiguration
{
	double dbAPR{ 0 }; //yaer apr

	void SetDailyAprdPercent(double dbDailyPercent) { dbAPR = dbDailyPercent / 100.0 * 365; }
	
	double GetRewardRatioByTimeframe(timeframe_t tf)
	{
		return (dbAPR / 365.0 / (double)timeframe_enum::Day1 * (double)tf);
	}
};

class CFarmingSimulator
{
public:
	typedef std::list<std::pair<stStakeConfiguration, stRewardWallet>> TlstStakeToWalletResults;
	typedef std::list<stStakeConfiguration> TlstStakeAutocompoundResults;

	typedef std::list<std::pair<stLpConfiguration, stRewardWallet>> TlstLpToWalletResults;
	typedef std::list<stLpConfiguration> TlstLpAutocompoundResults;

public:

	// --------------------------- complete simulation --------------------------- 
	TlstStakeToWalletResults SimulateStakingToRewardWallet(stRewardsConfiguration rewardCfg, stStepConfiguration stepCfg, stStakeConfiguration stakeCfg, size_t szSteps)
	{
		stRewardWallet rewardWallet;

		TlstStakeToWalletResults lstSteps;
		lstSteps.push_back(std::make_pair(stakeCfg, rewardWallet));

		for (size_t szStep : ax_range_numeric(szSteps))
		{
			XUNUSED_ALWAYS(szStep);
			stakeCfg = RecalculateStakeConfiguration(stakeCfg, stepCfg);
			rewardWallet = CalculateApyToStandaloneWallet(rewardCfg, stakeCfg, rewardWallet, stepCfg.tfStepLength);
			lstSteps.push_back(std::make_pair(stakeCfg, rewardWallet));
		}

		return lstSteps;
	}

	TlstStakeAutocompoundResults SimulateStakingAutocompound(stRewardsConfiguration rewardCfg, stStepConfiguration stepCfg, stStakeConfiguration stakeCfg, size_t szSteps)
	{
		TlstStakeAutocompoundResults lstSteps;
		lstSteps.push_back(stakeCfg);

		for (size_t szStep : ax_range_numeric(szSteps))
		{
			XUNUSED_ALWAYS(szStep);
			stakeCfg = RecalculateStakeConfiguration(stakeCfg, stepCfg);
			stakeCfg = CalculateApyToAutocompound(rewardCfg, stakeCfg, stepCfg.tfStepLength);
			lstSteps.push_back(stakeCfg);
		}

		return lstSteps;
	}

	TlstLpToWalletResults SimulateLpToRewardWallet(stRewardsConfiguration rewardCfg, stStepConfiguration stepCfg, stLpConfiguration lpCfg, size_t szSteps)
	{
		stRewardWallet rewardWallet;

		TlstLpToWalletResults lstSteps;
		lstSteps.push_back(std::make_pair(lpCfg, rewardWallet));

		for (size_t szStep : ax_range_numeric(szSteps))
		{
			XUNUSED_ALWAYS(szStep);
			lpCfg = RecalculateLpConfiguration(lpCfg, stepCfg);
			rewardWallet = CalculateApyToStandaloneWallet(rewardCfg, lpCfg, rewardWallet, stepCfg.tfStepLength);
			lstSteps.push_back(std::make_pair(lpCfg, rewardWallet));
		}

		return lstSteps;
	}

	TlstLpAutocompoundResults SimulateLpAutocompound(stRewardsConfiguration rewardCfg, stStepConfiguration stepCfg, stLpConfiguration lpCfg, size_t szSteps)
	{
		TlstLpAutocompoundResults lstSteps;
		lstSteps.push_back(lpCfg);

		for (size_t szStep : ax_range_numeric(szSteps))
		{
			XUNUSED_ALWAYS(szStep);
			lpCfg = RecalculateLpConfiguration(lpCfg, stepCfg);
			lpCfg = CalculateApyToAutocompound(rewardCfg, lpCfg, stepCfg.tfStepLength);
			lstSteps.push_back(lpCfg);
		}

		return lstSteps;
	}


	// --------------------------- Step simulation --------------------------- 
	stLpConfiguration RecalculateLpConfiguration(stLpConfiguration lpConfiguration, stStepConfiguration stepConfig)
	{
		//new token1 and token2 price
		double dbNewToken1Price = lpConfiguration.dbPriceToken1 * (1+stepConfig.dbPriceChangeToken1);
		double dbNewToken2Price = lpConfiguration.dbPriceToken2 * (1+stepConfig.dbPriceChangeToken2);

		//new token1 and token2 value after price change ($600 + $660 after 10% price increase on token2)
		double dbNewToken1Value = lpConfiguration.dbAmountToken1 * dbNewToken1Price;
		double dbNewToken2Value = lpConfiguration.dbAmountToken2 * dbNewToken2Price;

		//and new token average value to be in balance ($630 mid value)
		double dbNewMidValue = (dbNewToken1Value + dbNewToken2Value) / 2.0;
		
		//new amount of tokens ($630/$600 = 1.05 and $630/6.6 = 95,45)
		double dbNewAmountToken1 = dbNewMidValue / dbNewToken1Price;
		double dbNewAmountToken2 = dbNewMidValue / dbNewToken2Price;

		//result
		stLpConfiguration lpNewConfiguration;
		lpNewConfiguration.dbAmountLp = lpConfiguration.dbAmountLp;
		lpNewConfiguration.dbPriceToken1 = lpConfiguration.dbPriceToken1 * (1+stepConfig.dbPriceChangeToken1);
		lpNewConfiguration.dbPriceToken2 = lpConfiguration.dbPriceToken2 * (1+stepConfig.dbPriceChangeToken2);
		lpNewConfiguration.dbAmountToken1 = dbNewAmountToken1;
		lpNewConfiguration.dbAmountToken2 = dbNewAmountToken2;

		return lpNewConfiguration;
	}

	stStakeConfiguration RecalculateStakeConfiguration(stStakeConfiguration stakeConfiguration, stStepConfiguration stepConfig)
	{
		stakeConfiguration.dbPriceToken = stakeConfiguration.dbPriceToken * (1+stepConfig.dbPriceChangeToken1);
		return stakeConfiguration;
	}

	stRewardWallet CalculateApyToStandaloneWallet(stRewardsConfiguration rewardCfg, stLpConfiguration lpPair, stRewardWallet rewardWallet, timeframe_t tfPerid = timeframe_enum::Day1)
	{
		//APY per period
		double dbApyRatioPerPeriod = rewardCfg.GetRewardRatioByTimeframe(tfPerid);

		//gain in LP price currency ($$)
		double dbGainPerRatioInLpPrice = lpPair.GetTotalValue() * dbApyRatioPerPeriod;

		//recalculated gain in token amount
		double dbGainInToken1 = dbGainPerRatioInLpPrice / lpPair.dbPriceToken1;

		rewardWallet.dbRewardAmount += dbGainInToken1;
		rewardWallet.dbLastPrice = lpPair.dbPriceToken1;
		return rewardWallet;
	}

	stLpConfiguration CalculateApyToAutocompound(stRewardsConfiguration rewardCfg, stLpConfiguration lpPair, timeframe_t tfPerid = timeframe_enum::Day1)
	{
		//APY per period
		double dbApyRatioPerPeriod = rewardCfg.GetRewardRatioByTimeframe(tfPerid);

		//gain in LP price currency ($$)
		double dbGainPerRatioInLpPrice = lpPair.GetTotalValue() * dbApyRatioPerPeriod;

		//recalculated gain in token amount
		double dbGainInLpToken = dbGainPerRatioInLpPrice / lpPair.GetLpValue();
		lpPair.dbAmountLp += dbGainInLpToken;

		return lpPair;
	}

	stRewardWallet CalculateApyToStandaloneWallet(stRewardsConfiguration rewardCfg, stStakeConfiguration stakeConfiguration, stRewardWallet rewardWallet, timeframe_t tfPerid = timeframe_enum::Day1)
	{
		//APY per period
		double dbApyRatioPerPeriod = rewardCfg.GetRewardRatioByTimeframe(tfPerid);

		//gain in LP price currency ($$)
		double dbGainPerRatioInLpPrice = stakeConfiguration.GetTotalValue() * dbApyRatioPerPeriod;

		//recalculated gain in token amount
		double dbGainInRewardToken = dbGainPerRatioInLpPrice / stakeConfiguration.dbPriceToken;

		rewardWallet.dbRewardAmount += dbGainInRewardToken;
		rewardWallet.dbLastPrice = stakeConfiguration.dbPriceToken;
		return rewardWallet;
	}

	stStakeConfiguration CalculateApyToAutocompound(stRewardsConfiguration rewardCfg, stStakeConfiguration stakeConfiguration, timeframe_t tfPerid = timeframe_enum::Day1)
	{
		//APY per period
		double dbApyRatioPerPeriod = rewardCfg.GetRewardRatioByTimeframe(tfPerid);

		//gain in LP price currency ($$)
		double dbGainPerRatioInLpPrice = stakeConfiguration.GetTotalValue() * dbApyRatioPerPeriod;

		//recalculated gain in token amount
		double dbGainInRewardToken = dbGainPerRatioInLpPrice / stakeConfiguration.dbPriceToken;

		stakeConfiguration.dbAmountToken += dbGainInRewardToken;
		return stakeConfiguration;
	}
};