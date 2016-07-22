

#ifndef MockPlayer_h
#define MockPlayer_h

#include "gmock/gmock.h"
#include "IPlayer.h"

class MockPlayer : public  IPlayer {
public:
    MOCK_CONST_METHOD0( hasUnitAlive, bool() );
    MOCK_CONST_METHOD1( hasCapturedHQ, bool( const Player& enemy ) );
};

#endif /* MockPlayer_h */