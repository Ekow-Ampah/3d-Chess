#include "NetMsg.h"
#ifdef AFTR_CONFID_USE_BOOST
namespace AFTR{
  class NetMsgCreateRawwO: public NetMsg{
    public: 
  NetMsgMacroDeclaration(NetMsgCreateRawwO);
  NetMsgCreateRawwO();
  virtual ~NetMsgCreateRawwO();
  virtual bool toStream(NetMessengerStreamBuffter& os) const;
  virtual bool fromStream(NetMessengerStreamBuffter& is);
  virtual void onMessageArrvied();
  virtual std::string toString() const;

  unsigned int sizel
  float* vertices;
  protected:};
  
}
#endif