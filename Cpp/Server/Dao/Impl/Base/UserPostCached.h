#ifndef _USERPOST_DAO_CACHED_H_
#define _USERPOST_DAO_CACHED_H_
#include "Dao/UserPostDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
#include "framework/db/cached/cachednode.h"
#include "framework/db/cached/cachedbase.h"
#include "framework/util/lightlock.h"
#include "framework/db/fastdb/fastdb.h"
#include "framework/util/atomicoperation.h"
#include "set"
#include "map"
namespace Dao
{
    namespace Impl
    {
        class TUserPostCached
        {
        public:
            int postId;
            int userId;
            std::string title;
            std::string content;
            std::string imgList;
            int nlike;
            int ndislike;
            int ncomment;
            long64_t postDt;
            FASTDB_NS::dbFieldDescriptor* dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*);
            static FASTDB_NS::dbTableDescriptor dbDescriptor;
            void __update( const Message::Db::Tables::TUserPost& v );
            void __save( Message::Db::Tables::TUserPost& v ) const;
        };
        class CUserPostCached
                :public cdf::cached::CCachedDao,
                public cdf::cached::CCachedBase
        {
        public:
            typedef cdf::cached::CCachedNode< Message::Db::Tables::TUserPost> MEM_NODE;
            typedef cdf::CHandle< MEM_NODE > MEM_NODE_PTR;
            typedef std::map<int,MEM_NODE_PTR> MEM_NODE_MAP;
            typedef std::list<MEM_NODE_PTR> MEM_NODE_LIST;
            typedef std::map< cdf::CTransaction* , MEM_NODE_MAP > TRANSACTION_MAP;
            
            virtual bool get( int id , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update = false );
            virtual void save( Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt );
            virtual bool update( const Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt );
            virtual bool remove( int id , cdf::CStatement* stmt );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::Db::Tables::SeqTUserPost& v , cdf::CStatement* stmt , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::Db::Tables::TUserPost& v , cdf::CStatement* stmt , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::Db::Tables::TUserPost& v, cdf::CStatement* stmt );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt);
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt );
            
            virtual int getTotalCount();
            virtual void clear( cdf::CStatement* stmt );
            virtual void load( cdf::CStatement* stmt );
            virtual void flush( cdf::CStatement* stmt );
            virtual void rollback( cdf::CTransaction* tx );
            virtual void commit( cdf::CTransaction* tx );
            virtual void nagtive( cdf::CStatement* stmt );
            virtual void unnagtive( cdf::CStatement* stmt );
            virtual void cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt );
            virtual void cached( Message::Db::Tables::SeqTUserPost& v );
            virtual void evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt );
            
            static void regist();
            
        private:
            virtual MEM_NODE_PTR getNagtive( cdf::CStatement* stmt );
            virtual void __registToTx( 
            	cdf::CTransaction* tx , 
            	const TUserPostCached& table,
            	cdf::cached::ECachedUpdateModel model
            	);
            virtual void __update(
            	TUserPostCached& v,
            	const cdf::dao::SeqDataNode& seq 
            	);
            TRANSACTION_MAP _transactionNodes;
            MEM_NODE_MAP _flushMap;
            MEM_NODE_LIST _nagtiveList;
            cdf::CAtomic _id;
            cdf::CLightLock _lock;
            cdf::CLightLock _nagtiveLock;
            static cdf::CAutoRun _autoRun;
        };
    }
}
#endif

void cached( Message::Db::Tables::SeqTUserPost& v );