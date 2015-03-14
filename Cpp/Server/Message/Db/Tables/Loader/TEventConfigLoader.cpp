#include "Message/Db/Tables/Loader/TEventConfigLoader.h"
#include "fstream"
void
Message::Db::Tables::Loader::loadFile( const std::string& file ,Message::Db::Tables::SeqTEventConfig& vals )
{
    Json::Value json;
    Json::Reader reader;
    std::ifstream ifs( file.c_str() );
    reader.parse( ifs , json );
    Message::Db::Tables::TEventConfig val;
    for( Json::Value::UInt i = 0 ; i < json.size() ; i ++ )
    {
        fromJs( val , json[i] );
        vals.push_back( val );
    }
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TEventConfig& val , const std::string& js )
{
    Json::Value json;
    json.parse( js );
    fromJs( val , json );
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TEventConfig& val , std::string& js )
{
    Json::Value json;
    toJs( val , json );
    js = json.toFastString();
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TEventConfig& val , const Json::Value& json )
{
    val.eventId = json["eventId"].isNull() ? 0 : json["eventId"].asInt();
    val.event = json["event"].isNull() ? "" : json["event"].asString();
    val.inParams = json["inParams"].isNull() ? "" : json["inParams"].asString();
    val.outParams = json["outParams"].isNull() ? "" : json["outParams"].asString();
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TEventConfig& val , Json::Value& json )
{
    if( 0 != val.eventId )
    {
        json["eventId"] = Json::Value( val.eventId );
    }
    if( "" != val.event )
    {
        json["event"] = Json::Value( val.event );
    }
    if( "" != val.inParams )
    {
        json["inParams"] = Json::Value( val.inParams );
    }
    if( "" != val.outParams )
    {
        json["outParams"] = Json::Value( val.outParams );
    }
}