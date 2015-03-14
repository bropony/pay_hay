#include "Post.h"

using namespace WebServerApp;

CPost::CPost(const Message::Db::Tables::TUserPost & userPost)
:_tUserPost(userPost)
{

}

Message::Db::Tables::TUserPost & CPost::getTUserPost()
{
	return _tUserPost;
}
