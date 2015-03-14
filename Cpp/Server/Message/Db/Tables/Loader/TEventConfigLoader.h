#ifndef _TEVENTCONFIG_LOADER_H_
#define _TEVENTCONFIG_LOADER_H_
#include "Message/Db/Tables/TEventConfig.h"
#include "framework/json/json.h"
namespace Message
{
    namespace Db
    {
        namespace Tables
        {
            namespace Loader
            {
                
                void loadFile( const std::string& file , Message::Db::Tables::SeqTEventConfig& vals );
                void fromJs( Message::Db::Tables::TEventConfig& val , const std::string& js );
                void toJs( const Message::Db::Tables::TEventConfig& val , std::string& js );
                void fromJs( Message::Db::Tables::TEventConfig& val , const Json::Value& json );
                void toJs( const Message::Db::Tables::TEventConfig& val , Json::Value& json );
            }
        }
    }
}
#endif