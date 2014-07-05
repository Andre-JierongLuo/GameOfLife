#ifndef _YPANEL_H_
#define _YPANEL_H_

#include "YComponent.h"

  /**
   * A Panel is simply a Component which contains other Components. It
   * has no visual appearance of its own.
   */
class YPanel : public YComponent {
  public:
	string name;
    YPanel(const string & name);
};

#endif /* _YPANEL_H_ */

