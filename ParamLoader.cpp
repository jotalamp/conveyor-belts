#include "ParamLoader.h"

ParamLoader* ParamLoader::Instance()
{
  static ParamLoader instance;

  return &instance;
}

void ParamLoader::LoadValuesFromIni(ConfigFile* iniFile)
{
    //ConveyorBelt01Speed     = iniFile->GetInt("ConveyorBelt01", "Speed", 100);
    //ConveyorBelt02Speed     = iniFile->GetInt("ConveyorBelt02", "Speed", 100);
    //ConveyorBelt03Speed     = iniFile->GetInt("ConveyorBelt03", "Speed", 100);
    //ConveyorBelt04Speed     = iniFile->GetInt("ConveyorBelt04", "Speed", 100);




/*
    TimeScale               = iniFile->GetFloat("Time", "Scale", 1.0);

    SawBoardsMinDistance    = iniFile->GetInt(  "Saw",    "BoardsMinDistance", 2000);
    SawBoardsMaxDistance    = iniFile->GetInt(  "Saw",    "BoardsMaxDistance", 3000);

    PacketMaxBoards         = iniFile->GetInt(  "Packet", "MaxBoards", 10);
*/
/*
    struct Boards
    {
        String s = "Boards";
        float   Width       = iniFile->GetFloat(s, "Width",      48.0 );
        float   Height      = iniFile->GetFloat(s, "Height",     48.0 );
        int     MinLength   = iniFile->GetInt  (s, "Minlength",  160  );
        int     MaxLength   = iniFile->GetInt  (s, "Maxlength",  550  );
        int     Mass        = iniFile->GetInt  (s, "Mass",       500  );
        int     Friction    = iniFile->GetFloat(s, "Friction",   500  );
    };*/
/*
Friction=0.6
AngularDamping=0.8
CcdRadius=0.06
CcdMotionThreshold=2.0

[Pusher]
Limit=-7.14
Speed=4
HomePosition=-6.64
SlowingFactor=0.9
AccelerationFactor=4.0
AccelerationAdd=500.0
Delay=40

[ConveyorBelt01]
Width=200
Length=600
Radius=100
Speed=220
FrictionFactor=0.1

[ConveyorBelt02]
Width=200
Length=600
Radius=100
Speed=60
FrictionFactor=0.1

[ConveyorBelt03]
Width=200
Length=600
Radius=100
Speed=200
FrictionFactor=0.1

[ConveyorBelt04]
Width=200
Length=600
Radius=100
Speed=0
FrictionFactor=0.1

[Detector]
Length=0.1
LineColor=1.0 0.0 0.0 0.5

[FPS]
SmoothnessFactor=0.95

[Team1]
Name=Kappaletta
ShortName = KPL

[Team2]
Name=Metrejä
ShortName = MTR

[Camera]
FarClip=150.0
MaxZoom=9.0
MinZoom=0.8
MovingSpeed=0.1
MovingFactor=0.96

[FreeCamera]
MinAngle=0.1
MaxAngle=89.9
Offset=0.0 0.1 -10.0

[Sounds]
Music=0.9
Sound=0.9

[PostProcess]
BloomHDR=false
FXAA3=false
FXAA2=false
*/
    /*
    GoalWidth = iniFile->GetFloat("AI", "GoalWidth", 7.2f);

    DebugRender = iniFile->GetBool("Debug", "DebugRender", false);
    DrawSteering = iniFile->GetBool("Debug", "DrawSteering", false);

    NumSupportSpotsX = iniFile->GetInt("AI", "NumSupportSpotsX", 10);
    NumSupportSpotsY = iniFile->GetInt("AI", "NumSupportSpotsY", 10);

    Spot_PassSafeScore                     = iniFile->GetFloat("AI", "Spot_PassSafeScore", 10.0f);
    Spot_CanScoreFromPositionScore         = iniFile->GetFloat("AI", "Spot_CanScoreFromPositionScore", 10.0f);
    Spot_DistFromControllingPlayerScore     = iniFile->GetFloat("AI", "Spot_DistFromControllingPlayerScore", 10.0f);
    Spot_ClosenessToSupportingPlayerScore  = iniFile->GetFloat("AI", "Spot_ClosenessToSupportingPlayerScore", 10.0f);
    Spot_AheadOfAttackerScore              = iniFile->GetFloat("AI", "Spot_AheadOfAttackerScore", 10.0f);

    SupportSpotUpdateFreq       = iniFile->GetFloat("AI", "SupportSpotUpdateFreq", 10.0f);

    ChancePlayerAttemptsPotShot = iniFile->GetFloat("AI", "ChancePlayerAttemptsPotShot", 10.0f);
    ChanceOfUsingArriveTypeReceiveBehavior = iniFile->GetFloat("AI", "ChanceOfUsingArriveTypeReceiveBehavior", 10.0f);

    BallSize                    = iniFile->GetFloat("AI", "BallSize", 10.0f);
    BallMass                    = iniFile->GetFloat("AI", "BallMass", 10.0f);
    Friction                    = iniFile->GetFloat("AI", "Friction", 10.0f);

    KeeperInBallRange           = iniFile->GetFloat("AI", "KeeperInBallRange", 10.0f);
    PlayerInTargetRange         = iniFile->GetFloat("AI", "PlayerInTargetRange", 1.0f);
    PlayerKickingDistance       = iniFile->GetFloat("AI", "PlayerKickingDistance", 10.0f);
    PlayerKickFrequency         = iniFile->GetFloat("AI", "PlayerKickFrequency", 10.0f);


    PlayerMass                  = iniFile->GetFloat("AI", "PlayerMass", 10.0f);
    PlayerMaxForce              = iniFile->GetFloat("AI", "PlayerMaxForce", 10.0f);
    PlayerMaxSpeedWithBall      = iniFile->GetFloat("AI", "PlayerMaxSpeedWithBall", 10.0f);
    PlayerMaxSpeedWithoutBall   = iniFile->GetFloat("AI", "PlayerMaxSpeedWithoutBall", 10.0f);
    PlayerMaxTurnRate           = iniFile->GetFloat("AI", "PlayerMaxTurnRate", 10.0f);
    PlayerScale                 = iniFile->GetFloat("AI", "PlayerScale", 10.0f);
    PlayerComfortZone           = iniFile->GetFloat("AI", "PlayerComfortZone", 10.0f);
    PlayerKickingAccuracy       = iniFile->GetFloat("AI", "PlayerKickingAccuracy", 10.0f);

    NumAttemptsToFindValidStrike = iniFile->GetInt("AI", "NumAttemptsToFindValidStrike", 10);

    MaxDribbleForce             = iniFile->GetFloat("AI", "MaxDribbleForce", 10.0f);
    MaxShootingForce            = iniFile->GetFloat("AI", "MaxShootingForce", 30.0f);
    MinShootingForce            = iniFile->GetFloat("AI", "MaxShootingForce", 10.0f);
    MaxPassingForce             = iniFile->GetFloat("AI", "MaxPassingForce", 20.0f);

    WithinRangeOfHome           = iniFile->GetFloat("AI", "WithinRangeOfHome ", 10.0f);
    WithinRangeOfSupportSpot    = iniFile->GetFloat("AI", "WithinRangeOfSupportSpot", 10.0f);

    MinPassDist                 = iniFile->GetFloat("AI", "MinPassDist", 10.0f);
    GoalkeeperMinPassDist       = iniFile->GetFloat("AI", "GoalkeeperMinPassDist", 10.0f);

    GoalKeeperTendingDistance   = iniFile->GetFloat("AI", "GoalKeeperTendingDistance", 10.0f);
    GoalKeeperInterceptRange    = iniFile->GetFloat("AI", "GoalKeeperInterceptRange", 10.0f);
    BallWithinReceivingRange    = iniFile->GetFloat("AI", "BallWithinReceivingRange", 100.0f);

    bStates                     = iniFile->GetBool("AI", "bStates", true);
    bIDs                        = iniFile->GetBool("AI", "bIDs", true);
    bSupportSpots               = iniFile->GetBool("AI", "bSupportSpots", true);
    bRegions                    = iniFile->GetBool("AI", "bRegions", true);
    bShowControllingTeam        = iniFile->GetBool("AI", "bShowControllingTeam", true);
    bViewTargets                = iniFile->GetBool("AI", "bViewTargets", true);
    bHighlightIfThreatened      = iniFile->GetBool("AI", "bHighlightIfThreatened", true);

    FrameRate                   = iniFile->GetInt("AI", "FrameRate", 10);

    SeparationCoefficient       = iniFile->GetFloat("AI", "SeparationCoefficient", 10.0f);
    ViewDistance                = iniFile->GetFloat("AI", "ViewDistance", 10.0f);
    bNonPenetrationConstraint   = iniFile->GetBool("AI", "bNonPenetrationConstraint", true);

    BallWithinReceivingRangeSq = BallWithinReceivingRange * BallWithinReceivingRange;
    KeeperInBallRangeSq      = KeeperInBallRange * KeeperInBallRange;
    PlayerInTargetRangeSq    = PlayerInTargetRange * PlayerInTargetRange;
    PlayerKickingDistance   += BallSize;
    PlayerKickingDistanceSq  = PlayerKickingDistance * PlayerKickingDistance;
    PlayerComfortZoneSq      = PlayerComfortZone * PlayerComfortZone;
    GoalKeeperInterceptRangeSq     = GoalKeeperInterceptRange * GoalKeeperInterceptRange;
    WithinRangeOfSupportSpotSq = WithinRangeOfSupportSpot * WithinRangeOfSupportSpot;
    */
}
