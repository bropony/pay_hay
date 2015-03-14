#include "Message/Db/Tables/Loader/TErrorCodeLoader.h"
#include "fstream"
void
Message::Db::Tables::Loader::loadFile( const std::string& file ,Message::Db::Tables::SeqTErrorCode& vals )
{
    Json::Value json;
    Json::Reader reader;
    std::ifstream ifs( file.c_str() );
    reader.parse( ifs , json );
    Message::Db::Tables::TErrorCode val;
    for( Json::Value::UInt i = 0 ; i < json.size() ; i ++ )
    {
        fromJs( val , json[i] );
        vals.push_back( val );
    }
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TErrorCode& val , const std::string& js )
{
    Json::Value json;
    json.parse( js );
    fromJs( val , json );
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TErrorCode& val , std::string& js )
{
    Json::Value json;
    toJs( val , json );
    js = json.toFastString();
}
void
Message::Db::Tables::Loader::fromJs( Message::Db::Tables::TErrorCode& val , const Json::Value& json )
{
    val.errorCode = json["errorCode"].isNull() ? 0 : json["errorCode"].asInt();
    val.errorName = json["errorName"].isNull() ? "" : json["errorName"].asString();
    val.errorStr = json["errorStr"].isNull() ? "" : json["errorStr"].asString();
}
void
Message::Db::Tables::Loader::toJs( const Message::Db::Tables::TErrorCode& val , Json::Value& json )
{
    if( 0 != val.errorCode )
    {
        json["errorCode"] = Json::Value( val.errorCode );
    }
    if( "" != val.errorName )
    {
        json["errorName"] = Json::Value( val.errorName );
    }
    if( "" != val.errorStr )
    {
        json["errorStr"] = Json::Value( val.errorStr );
    }
}