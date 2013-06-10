#ifndef REMOTEMSGMGR_H_INCLUDED
#define REMOTEMSGMGR_H_INCLUDED

class RemoteMsgMgr
{
public:
    RemoteMsgMgr();
    void Listen();
    void Send(byte* frame);
};

#endif // REMOTEMSGMGR_H_INCLUDED
