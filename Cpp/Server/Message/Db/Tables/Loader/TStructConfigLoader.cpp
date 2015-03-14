#include "Message/Db/Tables/Loader/TStructConfigLoader.h"
#include "fstream"
void
Message::Db::Tables::Loader::loadFile( const std::string& file ,Message::Db::Tables::SeqTStructConfig& vals )
{
    Json::Value json;
    Json::Reader reader;
    std::ifstream ifs( file.c_str() );
    reader.parse( ifs , json );
    Message::Db::Tables::TStructConfig val;
    for( Json::Value::UInt i = 0 ; i < json.size() ; i ++ )
    {
        fromJs( val , json[i] );
        vals.push_back( val );
    }
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TStructConfig& val , const std::string& js )
{
    Json::Value json;
    json.parse( js );
    fromJs( val , json );
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TStructConfig& val , std::string& js )
{
    Json::Value json;
    toJs( val , json );
    js = json.toFastString();
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TStructConfig& val , const Json::Value& json )
{
    val.name = json["name"].isNull() ? "" : json["name"].asString();
    val.type = json["type"].isNull() ? 0 : json["type"].asInt();
    val.fields = json["fields"].isNull() ? "" : json["fields"].asString();
    val.descr = json["descr"].isNull() ? "" : json["descr"].asString();
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TStructConfig& val , Json::Value& json )
{
    if( "" != val.name )
    {
        json["name"] = Json::Value( val.name );
    }
    if( 0 != val.type )
    {
        json["type"] = Json::Value( val.type );
    }
    if( "" != val.fields )
    {
        json["fields"] = Json::Value( val.fields );
    }
    if( "" != val.descr )
    {
        json["descr"] = Json::Value( val.descr );
    }
}