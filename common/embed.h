#ifndef __embed_h_
#define __embed_h_

#include "prtypes.h"

// XXX
typedef PRUint32 nsresult;

class MozViewListener;
class WindowCreator;

class MozApp
{
public:
  MozApp(const char* aProfilePath = 0);
  virtual ~MozApp();

  nsresult SetCharPref(const char *name, const char *value);
  nsresult SetBoolPref(const char *name, PRBool value);
  nsresult SetIntPref(const char *name, int value);

  nsresult GetCharPref(const char *name, char **value);
  nsresult GetBoolPref(const char *name, PRBool *value);
  nsresult GetIntPref(const char *name, int *value);

 private:
  class Private;
  Private *mPrivate;
};


class MozView
{
public:
  MozView();
  virtual ~MozView();

  nsresult CreateBrowser(void* aNativeWindow, PRInt32 x, PRInt32 y,
    PRInt32 width, PRInt32 height);
  nsresult SetPositionAndSize(PRInt32 x, PRInt32 y,
    PRInt32 width, PRInt32 height);
  nsresult LoadURI(const char* uri);
  nsresult LoadData(const char    *base_url,
		    const char    *content_type,
		    const PRUint8 *data,
		    PRUint32       len);

  nsresult SetFocus(PRBool focus);

  void Show();
  void Hide();

  void SetListener(MozViewListener* pNewListener);
  MozViewListener* GetListener();

  void* GetParentWindow();
  void *GetNativeWindow();

private:
  class Private;
  Private *mPrivate;

  friend class WindowCreator;
};

/**
 * This is the callback interface to the embedding app.
 * The app can subclass this and override methods that will
 * be called as appropriate.
 *
 * Use MozView::SetListener to regster the listener
 *
 * MozViewListener implements noop defaults, so the app only
 * needs to override the methods it uses.
 */
class MozViewListener
{
public:
  MozViewListener();
  virtual ~MozViewListener();
  void SetMozView(MozView* pAMozView);

  // methods the embedding app can override
  virtual void SetTitle(const char* newTitle);
  virtual void StatusChanged(const char* newStatus, PRUint32 statusType);
  virtual void LocationChanged(const char* newLocation);
  virtual PRBool OpenURI(const char* newLocation);
  virtual void DocumentLoaded();
  virtual MozView* OpenWindow(PRUint32 flags);

protected:
  MozView* pMozView;
};

#endif /* __embed_h_ */

