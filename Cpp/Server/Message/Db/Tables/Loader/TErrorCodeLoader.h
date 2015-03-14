#ifndef _TERRORCODE_LOADER_H_
#define _TERRORCODE_LOADER_H_
#include "Message/Db/Tables/TErrorCode.h"
#include "framework/json/json.h"
namespace Message
{
    namespace Db
    {
        namespace Tables
        {
            namespace Loader
            {
                
                void loadFile( const std::string& file , Message::Db::Tables::SeqTErrorCode& vals );
                void fromJs( Message::Db::Tables::TErrorCode& val , const std::string& js );
                void toJs( const Message::Db::Tables::TErrorCode& val , std::string& js );
                void fromJs( Message::Db::Tables::TErrorCode& val , const Json::Value& json );
                void toJs( const Message::Db::Tables::TErrorCode& val , Json::Value& json );
            }
        }
    }
}
#endif