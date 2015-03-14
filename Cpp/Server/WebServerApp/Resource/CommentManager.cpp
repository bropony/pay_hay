#include "CommentManager.h"

using namespace WebServerApp;

CCommentManager * CCommentManager::instance()
{
	static CCommentManager _inst;

	return &_inst;
}

void CCommentManager::loadAllComments()
{

}
