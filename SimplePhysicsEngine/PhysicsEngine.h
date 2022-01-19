#ifndef SIMPLEPHYSICSENGINE_PHYSICSWORLD_H
#define SIMPLEPHYSICSENGINE_PHYSICSWORLD_H
#include <algorithm>
#include <thread>
#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>

#include "Object.h"
#include "MeshCollider.h"
#include "Simplex.h"

namespace SimplePhysicsEngine
{   
    struct PhysicsData
    {
        utils::Vector3 position;
        utils::Vector3 rotation;
        utils::Vector3 velocity;
        utils::Vector3 forces;
        AABB aabb;
        MeshCollider collider;

        float mass;
        bool isKinematic;

        PhysicsData(utils::Vector3 position, utils::Vector3 rotation, utils::Vector3 velocity, utils::Vector3 forces, MeshCollider collider, AABB aabb, float mass, bool isKinematic)
            :position(position), rotation(rotation), velocity(velocity), forces(forces), mass(mass), isKinematic(isKinematic), collider(collider), aabb(aabb)
        {}        
    };

    struct Collisions
    {
        int aInd;
        int bInd;
    };

    class PhysicsEngine 
    {
    private:
        utils::Vector3 defaultGravity{ 0,-0.098f,0 };
        std::thread physicsThread;
                
//critical section
        std::vector<PhysicsData> simulateBuffer;
        std::vector<Object*> latestBuffer;
        std::vector<Object*> waitingObjects;
        std::vector<int> waitingRemoveTargets;

        int nextID=0;

        std::mutex sBufferLock;
        std::mutex lBufferLock;
        std::mutex woBufferLock;
        std::mutex rtBufferLock;

        [[noreturn]] void threadPhysicsUpdate();        

        void addObjectsAtWaitingQueue();
        void removeObjectsAtWaitingQueue();

        //test
        void PreDetectCollision();
        void SecondDetectCollision();

        bool GJK(const MeshCollider* colliderA, utils::Vector3 posA, const MeshCollider* colliderB, utils::Vector3 posB);
        utils::Vector3 Support(const MeshCollider* colliderA, const MeshCollider* colliderB, utils::Vector3 dir);
        bool NextSimplex(Simplex& points, utils::Vector3& dir);
        bool SameDirection(const utils::Vector3& dir, const utils::Vector3 ao);
        bool Line(Simplex& points, utils::Vector3& dir);
        bool Triangle(Simplex& points, utils::Vector3& dir);
        bool Tetrahedron(Simplex& points, utils::Vector3& dir);

    public:           
        static PhysicsData PhysicsCopy(const Object& origin);

        void runPhysicsThread();
        void addObject(Object* obj);
        void removeObject(int ID);
        void updatePhysics(float dt);

        int getObjectsNumber() { return latestBuffer.size(); };
        std::vector<Object*> getLatestBuffer() { return latestBuffer; };
    };
}

#endif //SIMPLEPHYSICSENGINE_PHYSICSWORLD_H
