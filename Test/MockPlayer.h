

#ifndef MockPlayer_h
#define MockPlayer_h

#include "gmock/gmock.h"
#include "IPlayer.h"

class MockPlayer : public  IPlayer {
public:
    MOCK_METHOD0( hasUnitAlive, bool() );
    MOCK_METHOD0( hasCapturedHQ, bool() );
};

#endif /* MockPlayer_h */