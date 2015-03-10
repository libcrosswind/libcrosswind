



class cw::physics::box: public cw::physics::rigid_body{
public:
    box(const float& mass,
        const glm::vec3& origin,
        const glm::vec3& size): rigid_body(origin){

            init(mass,
                 new btDefaultMotionState(transform),
                 new btBoxShape(btVector3(size.x, size.y, size.z)));

    }

};

