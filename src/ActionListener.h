#ifndef _ACTIONLISTENER_H_
#define _ACTIONLISTENER_H_

#include "YComponent.h"

class ActionListener{
public:
	virtual void ActionPerformed(YComponent* c) = 0;
};

#endif /* _ACTIONLISTENER_H_ */

