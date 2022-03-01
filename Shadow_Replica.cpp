
#include "Shadow_Replica.h"

// JSON RPC part
#include <stdlib.h>
#include "minigfs_client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

Shadow_Replica::Shadow_Replica
(std::string arg_host_url, std::string arg_vsID, std::string arg_class_id,
 std::string arg_object_id)
  : Replica { arg_host_url, arg_vsID, arg_class_id, arg_object_id }
{
  std::cout << "Shadow created" << std::endl;
}

Json::Value
Shadow_Replica::CommitAbort
(std::string arg_name, std::string arg_fhandle, std::string arg_chunk_index,
 std::string arg_commitorabort)
{
  HttpClient httpclient((this->host_url).c_str());
  minigfs_Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    std::cout << "calling NFS LookUp" << std::endl;

    myv = myClient.CommitAbort("CommitAbort", "This is a Directory JSON string!",
			       arg_chunk_index,
			       (this->class_id).c_str(), arg_commitorabort, arg_fhandle, arg_name,
			       (this->host_url).c_str(),
			       (this->object_id).c_str(), (this->owner_vsID).c_str());
    cout << myv.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  return myv;
}

Json::Value
Shadow_Replica::PushChunk2Replica
(std::string arg_name, std::string arg_fhandle, std::string arg_chunk_index, std::string arg_chunk)
{
  HttpClient httpclient((this->host_url).c_str());
  minigfs_Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    std::cout << "calling NFS LookUp" << std::endl;

    myv = myClient.PushChunk2Replica("PushChunk2Replica", "This is a Directory JSON string!",
				     arg_chunk, arg_chunk_index,
				     (this->class_id).c_str(), arg_fhandle, arg_name,
				     (this->host_url).c_str(),
				     (this->object_id).c_str(), (this->owner_vsID).c_str());
    cout << myv.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  return myv;
}

Json::Value *
Shadow_Replica::dumpJ
()
{
  HttpClient httpclient((this->host_url).c_str());
  minigfs_Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    std::cout << "calling NFS dumpJ" << std::endl;

    myv = myClient.dumpJ("dumpJ", "This is a Directory JSON string!",
			 (this->class_id).c_str(), (this->host_url).c_str(),
			 (this->object_id).c_str(), (this->owner_vsID).c_str());
    cout << myv.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  Json::Value *myv_ptr = new Json::Value();
  (*myv_ptr) = myv;
  return myv_ptr;
}

bool
Shadow_Replica::Jdump
(Json::Value *mjv_ptr)
{
  return false;
}
