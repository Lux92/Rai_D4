//
// Generated file, do not edit! Created by nedtool 5.0 from Datapacket.msg.
//

#ifndef __DATAPACKET_M_H
#define __DATAPACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
typedef double **Matrice;
// }}

/**
 * Class generated from <tt>Datapacket.msg:26</tt> by nedtool.
 * <pre>
 * packet Datapacket
 * {
 *     int idSource;
 *     Matrice matrice;
 *     int idDest;
 * }
 * </pre>
 */
class Datapacket : public ::omnetpp::cPacket
{
  protected:
    int idSource;
    Matrice matrice;
    int idDest;

  private:
    void copy(const Datapacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Datapacket&);

  public:
    Datapacket(const char *name=nullptr, int kind=0);
    Datapacket(const Datapacket& other);
    virtual ~Datapacket();
    Datapacket& operator=(const Datapacket& other);
    virtual Datapacket *dup() const {return new Datapacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getIdSource() const;
    virtual void setIdSource(int idSource);
    virtual Matrice& getMatrice();
    virtual const Matrice& getMatrice() const {return const_cast<Datapacket*>(this)->getMatrice();}
    virtual void setMatrice(const Matrice& matrice);
    virtual int getIdDest() const;
    virtual void setIdDest(int idDest);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Datapacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Datapacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>Datapacket.msg:31</tt> by nedtool.
 * <pre>
 * packet Applicationpacket
 * {
 *     simtime_t genTime;
 *     simtime_t arrivTime;
 * }
 * </pre>
 */
class Applicationpacket : public ::omnetpp::cPacket
{
  protected:
    ::omnetpp::simtime_t genTime;
    ::omnetpp::simtime_t arrivTime;

  private:
    void copy(const Applicationpacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Applicationpacket&);

  public:
    Applicationpacket(const char *name=nullptr, int kind=0);
    Applicationpacket(const Applicationpacket& other);
    virtual ~Applicationpacket();
    Applicationpacket& operator=(const Applicationpacket& other);
    virtual Applicationpacket *dup() const {return new Applicationpacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual ::omnetpp::simtime_t getGenTime() const;
    virtual void setGenTime(::omnetpp::simtime_t genTime);
    virtual ::omnetpp::simtime_t getArrivTime() const;
    virtual void setArrivTime(::omnetpp::simtime_t arrivTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Applicationpacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Applicationpacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef __DATAPACKET_M_H

