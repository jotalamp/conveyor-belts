#ifndef PARAMLOADER
#define PARAMLOADER
#pragma warning(disable:4800)
//------------------------------------------------------------------------
//
//Name:  ParamLoader.h
//
//Desc:  singleton class to handle the loading of default parameter
//       values from an initialization file: 'params.ini'
//
//Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
//#include <fstream>
//#include <string>
//#include <cassert>
#include "ConfigFile.h"


//#include "constants.h"
//#include "misc/iniFileLoaderBase.h"

using namespace Urho3D;


#define Prm (*ParamLoader::Instance())

class ParamLoader
{
private:
  ParamLoader()
  {
  }

public:

  static ParamLoader* Instance();

  void LoadValuesFromIni(ConfigFile* iniFile);

  bool DebugRender;
  bool DrawSteering;

  double GoalWidth;

  int   NumSupportSpotsX;
  int   NumSupportSpotsY;

  //these values tweak the various rules used to calculate the support spots
  double Spot_PassSafeScore;
  double Spot_CanScoreFromPositionScore;
  double Spot_DistFromControllingPlayerScore;
  double Spot_ClosenessToSupportingPlayerScore;
  double Spot_AheadOfAttackerScore;

  double SupportSpotUpdateFreq ;

  double ChancePlayerAttemptsPotShot;
  double ChanceOfUsingArriveTypeReceiveBehavior;

  double BallSize;
  double BallMass;
  double Friction;

  double KeeperInBallRange;
  double KeeperInBallRangeSq;

  double PlayerInTargetRange;
  double PlayerInTargetRangeSq;

  double PlayerMass;

  //max steering force
  double PlayerMaxForce;
  double PlayerMaxSpeedWithBall;
  double PlayerMaxSpeedWithoutBall;
  double PlayerMaxTurnRate;
  double PlayerScale;
  double PlayerComfortZone;

  double PlayerKickingDistance;
  double PlayerKickingDistanceSq;

  double PlayerKickFrequency;

  double  MaxDribbleForce;
  double  MaxShootingForce;
  double  MinShootingForce;
  double  MaxPassingForce;

  double  PlayerComfortZoneSq;

  //in the range zero to 1.0. adjusts the amount of noise added to a kick,
  //the lower the value the worse the players get
  double  PlayerKickingAccuracy;

  //the number of times the SoccerTeam::CanShoot method attempts to find
  //a valid shot
  int    NumAttemptsToFindValidStrike;

  //the distance away from the center of its home region a player
  //must be to be considered at home
  double WithinRangeOfHome;

  //how close a player must get to a sweet spot before he can change state
  double WithinRangeOfSupportSpot;
  double WithinRangeOfSupportSpotSq;


  //the minimum distance a receiving player must be from the passing player
  double   MinPassDist;
  double   GoalkeeperMinPassDist;

  //this is the distance the keeper puts between the back of the net
  //and the ball when using the interpose steering behavior
  double  GoalKeeperTendingDistance;

  //when the ball becomes within this distance of the Player he
  //changes state to intercept the ball
  double  GoalKeeperInterceptRange;
  double  GoalKeeperInterceptRangeSq;

  //how close the ball must be to a receiver before he starts chasing it
  double  BallWithinReceivingRange;
  double  BallWithinReceivingRangeSq;


  //these values control what debug info you can see
  bool  bStates;
  bool  bIDs;
  bool  bSupportSpots;
  bool  bRegions;
  bool  bShowControllingTeam;
  bool  bViewTargets;
  bool  bHighlightIfThreatened;

  int FrameRate;


  double SeparationCoefficient;

  //how close a neighbour must be before an agent perceives it
  double ViewDistance;

  //zero this to turn the constraint off
  bool bNonPenetrationConstraint;

};

#endif
