//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//             Coin Object Pool (cpp)
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
#include <iostream>
#include "CoinObjectPool.h"



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Coin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Coin::Coin() 
    : m_remainingLifetimeFrames(0)
{
}

void Coin::Activate(int _maxFrames)
{
    m_remainingLifetimeFrames = _maxFrames;
}

void Coin::Deactivate()
{
    m_remainingLifetimeFrames = 0;
}

CoinState Coin::Update()
{
    if (m_remainingLifetimeFrames > 0)
    {
        --m_remainingLifetimeFrames;
        if (m_remainingLifetimeFrames < 1)
        {
            return CoinState::FREED;
        }
        
        return CoinState::ACTIVE;
    }

    return CoinState::FREE;
}

bool Coin::GetIsActive()
{
    return m_remainingLifetimeFrames > 0;
}

int Coin::GetRemainingLifetimeFrames()
{
    return m_remainingLifetimeFrames;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//              Coin Object Pool
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// @brief Constructor for the CoinObjectPool.
// @param _poolSize The total number of coins to pre-allocate.
CoinObjectPool::CoinObjectPool(int _poolSize)
{
    m_allCoins.reserve(_poolSize);
    for (int i = 0; i < _poolSize; ++i)
    {
        m_allCoins.emplace_back();
        m_freeCoins.push_back(&m_allCoins.back());
    }
}

CoinObjectPool::~CoinObjectPool()
{
    // Since all coins are managed by std::vector we don't have any memory management we need to clear here.
}


// @brief Acquires an inactive coin from the pool.
// @param _lifetimeFrames Number of Frames the coin will exist for before dying of """natural causes""".
// @return A pointer to an active Coin object, or nullptr if the pool is exhausted.
Coin* CoinObjectPool::TrySpawnCoin(int _lifetimeFrames)
{
    if (m_freeCoins.empty())
    {
        std::cerr << "Warning: Coin pool exhausted! Cannot acquire more coins." << std::endl;
        return nullptr;
    }

    // Get a coin from the free list. Fetching from back to avoid vector element swapping overhead
    Coin* coin = m_freeCoins.back();
    m_freeCoins.pop_back();

    coin->Activate(_lifetimeFrames);
    m_activeCoins.push_back(coin);

    return coin;
}


// @brief Releases an active coin back to the pool.
// This happens when the player collects it, or when its lifetime expires.
// @param coin A pointer to the Coin object to release. Must not be nullptr.
void CoinObjectPool::ReleaseCoin(Coin* _coin) 
{
    if (_coin == nullptr)
    {
        std::cerr << "Error: Attempted to release a nullptr coin." << std::endl;
        return;
    }

    _coin->Deactivate();

    auto it = std::find(m_activeCoins.begin(), m_activeCoins.end(), _coin);
    if (it != m_activeCoins.end())
    {
        // Swap with last element and pop_back for O(1) removal. The order of the coins in
        // this list is not important at all, so swapping has no problems. Then re-add to Free Coins list
        std::swap(*it, m_activeCoins.back());
        m_activeCoins.pop_back();
        m_freeCoins.push_back(_coin);
    }
    else
    {
        std::cerr << "Error: Coin to release not found in activeCoins list. Pool integrity issue." << std::endl;
    }
}


// @brief Updates the state of all active coins.
// This method should be called once per game frame.
// It handles coins disappearing after their lifetime expires.
void CoinObjectPool::Update()
{
    // Iterate from back to front so we can modify the list freely
    for (size_t i = m_activeCoins.size() - 1; i != (size_t)(-1); --i)
    {
        Coin* coin = m_activeCoins[i];
        CoinState coinState = coin->Update();
        if (coinState == CoinState::FREED)
        {
            std::cout << "Coin expired due to lifetime. Releasing." << std::endl;
            ReleaseCoin(coin);       
        }
    }
}

size_t CoinObjectPool::GetActiveCoinCount() const
{
    return m_activeCoins.size();
}

size_t CoinObjectPool::GetFreeCoinCount() const
{
    return m_freeCoins.size();
}

size_t CoinObjectPool::GetTotalCoinCount() const
{
    return m_allCoins.size();
}