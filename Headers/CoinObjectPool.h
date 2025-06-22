//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Coin Object Pool (h)
//             Author: Christopher A
//             Date: June 22, 2025
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Description:
//
//		We are making an action game (2D/3D is irrelevant).
//      In game we need to make coins appear when the player destroys enemies or objects.
//      
//      Please implement an object pool so that we don't have to allocate those coins
//      all the time. 
// 
//      In this question we are only interested in the pool logic(api and implementation)
//      so there is no need to worry about details such as rendering and effects. 
//      The implementation is up to you but please try to fulfill at least those conditions:
//
//      - 10000 coins are allocated at init time
//      - no allocation happens after that during the game
//      - coins disapears when the player takes them
//      - coins disappears after 300 frame
//
//      class Coin
//      {
//      }
//
//      class CoinObjectPool
//      {
//      }
//
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef     __COIN_OBJECT_POOL_H_
#define     __COIN_OBJECT_POOL_H_


#include <vector>


enum CoinState
{
    FREE        = 0,
    FREED       = 1,
    ACTIVE      = 2,
};



class Coin
{
public:

    Coin();
    void Activate(int _maxFrames);
    void Deactivate();

    CoinState Update();

    bool GetIsActive();
    int GetRemainingLifetimeFrames();

private:
    int m_remainingLifetimeFrames;
};



class CoinObjectPool
{
public:
    
    // @brief Constructor for the CoinObjectPool.
    // @param _poolSize The total number of coins to pre-allocate.
    CoinObjectPool(int _poolSize = 10000);
    ~CoinObjectPool();

    
    // @brief Acquires an inactive coin from the pool.
    // @param _lifetimeFrames Number of Frames the coin will exist for before dying of """natural causes""".
    // @return A pointer to an active Coin object, or nullptr if the pool is exhausted.
    Coin* TrySpawnCoin(int _lifetimeFrames = 300);

    
    // @brief Releases an active coin back to the pool.
    // This happens when the player collects it, or when its lifetime expires.
    // @param _coin A pointer to the Coin object to release. Must not be nullptr.
    void ReleaseCoin(Coin* _coin);

    
    // @brief Updates the state of all active coins.
    // This method should be called once per game frame.
    // It handles coins disappearing after their lifetime expires.
    void Update();


    size_t GetActiveCoinCount() const;
    size_t GetFreeCoinCount() const;
    size_t GetTotalCoinCount() const;


private:
    std::vector<Coin> m_allCoins;
    std::vector<Coin*> m_freeCoins;
    std::vector<Coin*> m_activeCoins;
};



#endif  //  __COIN_OBJECT_POOL_H_