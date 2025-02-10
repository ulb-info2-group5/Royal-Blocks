#ifndef ICONNEXION_HPP
#define ICONNEXION_HPP

class IConnexion 
{
    public:

    virtual ~IConnexion() = 0;

    virtual void changeUserState() = 0;

// to implement later because idk how the DB works
};

#endif