#ifndef _TSTRUCTCONFIG_LOADER_H_
#define _TSTRUCTCONFIG_LOADER_H_
#include "Message/Db/Tables/TStructConfig.h"
#include "framework/json/json.h"
namespace Message
{
    namespace Db
    {
        namespace Tables
        {
            namespace Loader
            {
                
                void loadFile( const std::string& file , Message::Db::Tables::SeqTStructConfig& vals );
                void fromJs( Message::Db::Tables::TStructConfig& val , const std::string& js );
                void toJs( const Message::Db::Tables::TStructConfig& val , std::string& js );
                void fromJs( Message::Db::Tables::TStructConfig& val , const Json::Value& json );
                void toJs( const Message::Db::Tables::TStructConfig& val , Json::Value& json );
            }
        }
    }
}
#endif