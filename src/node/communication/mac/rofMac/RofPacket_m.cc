//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/mac/rofMac/RofPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RofPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(RofPacket);

RofPacket::RofPacket(const char *name, int kind) : ::MacPacket(name,kind)
{
    this->senderX_var = 0;
    this->senderY_var = 0;
    this->senderID_var = 0;
    this->packetType_var = 0;
    this->packetID_var = 0;
    this->sinkAddress_var = 0;
}

RofPacket::RofPacket(const RofPacket& other) : ::MacPacket(other)
{
    copy(other);
}

RofPacket::~RofPacket()
{
}

RofPacket& RofPacket::operator=(const RofPacket& other)
{
    if (this==&other) return *this;
    ::MacPacket::operator=(other);
    copy(other);
    return *this;
}

void RofPacket::copy(const RofPacket& other)
{
    this->senderX_var = other.senderX_var;
    this->senderY_var = other.senderY_var;
    this->senderID_var = other.senderID_var;
    this->packetType_var = other.packetType_var;
    this->packetID_var = other.packetID_var;
    this->sinkAddress_var = other.sinkAddress_var;
}

void RofPacket::parsimPack(cCommBuffer *b)
{
    ::MacPacket::parsimPack(b);
    doPacking(b,this->senderX_var);
    doPacking(b,this->senderY_var);
    doPacking(b,this->senderID_var);
    doPacking(b,this->packetType_var);
    doPacking(b,this->packetID_var);
    doPacking(b,this->sinkAddress_var);
}

void RofPacket::parsimUnpack(cCommBuffer *b)
{
    ::MacPacket::parsimUnpack(b);
    doUnpacking(b,this->senderX_var);
    doUnpacking(b,this->senderY_var);
    doUnpacking(b,this->senderID_var);
    doUnpacking(b,this->packetType_var);
    doUnpacking(b,this->packetID_var);
    doUnpacking(b,this->sinkAddress_var);
}

double RofPacket::getSenderX() const
{
    return senderX_var;
}

void RofPacket::setSenderX(double senderX)
{
    this->senderX_var = senderX;
}

double RofPacket::getSenderY() const
{
    return senderY_var;
}

void RofPacket::setSenderY(double senderY)
{
    this->senderY_var = senderY;
}

int RofPacket::getSenderID() const
{
    return senderID_var;
}

void RofPacket::setSenderID(int senderID)
{
    this->senderID_var = senderID;
}

int RofPacket::getPacketType() const
{
    return packetType_var;
}

void RofPacket::setPacketType(int packetType)
{
    this->packetType_var = packetType;
}

int RofPacket::getPacketID() const
{
    return packetID_var;
}

void RofPacket::setPacketID(int packetID)
{
    this->packetID_var = packetID;
}

int RofPacket::getSinkAddress() const
{
    return sinkAddress_var;
}

void RofPacket::setSinkAddress(int sinkAddress)
{
    this->sinkAddress_var = sinkAddress;
}

class RofPacketDescriptor : public cClassDescriptor
{
  public:
    RofPacketDescriptor();
    virtual ~RofPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(RofPacketDescriptor);

RofPacketDescriptor::RofPacketDescriptor() : cClassDescriptor("RofPacket", "MacPacket")
{
}

RofPacketDescriptor::~RofPacketDescriptor()
{
}

bool RofPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RofPacket *>(obj)!=NULL;
}

const char *RofPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RofPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int RofPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *RofPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "senderX",
        "senderY",
        "senderID",
        "packetType",
        "packetID",
        "sinkAddress",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int RofPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderX")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderY")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderID")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetType")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetID")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkAddress")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RofPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *RofPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int RofPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RofPacket *pp = (RofPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RofPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RofPacket *pp = (RofPacket *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getSenderX());
        case 1: return double2string(pp->getSenderY());
        case 2: return long2string(pp->getSenderID());
        case 3: return long2string(pp->getPacketType());
        case 4: return long2string(pp->getPacketID());
        case 5: return long2string(pp->getSinkAddress());
        default: return "";
    }
}

bool RofPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RofPacket *pp = (RofPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSenderX(string2double(value)); return true;
        case 1: pp->setSenderY(string2double(value)); return true;
        case 2: pp->setSenderID(string2long(value)); return true;
        case 3: pp->setPacketType(string2long(value)); return true;
        case 4: pp->setPacketID(string2long(value)); return true;
        case 5: pp->setSinkAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *RofPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *RofPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RofPacket *pp = (RofPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


