#pragma once

#include <Tempest/Event>
#include <Tempest/Matrix4x4>
#include <Tempest/Point>
#include <array>
#include <daedalus/DaedalusStdlib.h>

class World;
class Npc;
class Gothic;
class Serialize;

class Camera final {
  public:
    Camera(Gothic& gothic);

    enum Mode {
      Dialog,
      Normal,
      Inventory,
      Melee,
      Ranged,
      Magic
      };

    void reset();
    void save(Serialize &s);
    void load(Serialize &s,Npc* pl);

    void changeZoom(int delta);
    Tempest::PointF getSpin() const { return spin; }

    void rotateLeft ();
    void rotateRight();

    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();

    void setMode(Mode m);
    void follow(const Npc& npc, uint64_t dt, bool inMove, bool includeRot);

    void setPosition(float x,float y,float z);
    void setSpin(const Tempest::PointF& p);
    void setDestSpin(const Tempest::PointF& p);
    void setDistance(float d);

    Tempest::Matrix4x4 view() const;
    Tempest::Matrix4x4 viewShadow(const std::array<float,3> &ldir,int layer) const;

  private:
    Gothic&               gothic;
    Tempest::Vec3         camPos={};
    bool                  isInMove=false;
    Tempest::Vec3         camBone={};
    Tempest::PointF       spin, destSpin;
    float                 zoom=1.f;
    float                 dist=3.f;

    bool                  hasPos=false;
    Mode                  camMod=Normal;

    void implReset(const Npc& pl);
    void implMove(Tempest::KeyEvent::KeyType t);
    Tempest::Matrix4x4 mkView(float dist) const;

    const Daedalus::GEngineClasses::CCamSys& cameraDef() const;
    void clampZoom(float& z);
  };
