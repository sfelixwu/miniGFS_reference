
#include "Directory.h"

Dirent::Dirent()
{
  this->name = "";
  this->fhandle = "";
}

Dirent::Dirent(std::string arg_name, std::string arg_fhandle)
{
  this->name = arg_name;
  this->fhandle = arg_fhandle;
}

Json::Value *
Dirent::dumpJ()
{
  Json::Value * result_ptr = new Json::Value();

  if (this->name != "")
    {
      (*result_ptr)["name"] = this->name;
    }

  if (this->fhandle != "")
    {
      (*result_ptr)["fhandle"] = this->fhandle;
    }
  return result_ptr;
}

bool
Dirent::Jdump(Json::Value *input_json_ptr)
{
  if ((input_json_ptr == NULL) ||
      ((*input_json_ptr).isNull() == true) ||
      ((*input_json_ptr).isObject() != true))
    {
      return false;
    }

  if ((((*input_json_ptr)["name"]).isNull() == true) ||
      (((*input_json_ptr)["fhandle"]).isNull() == true) ||
      (((*input_json_ptr)["name"]).isString() != true) ||
      (((*input_json_ptr)["fhandle"]).isString() != true))
    {
      return false;
    }

  this->name    = ((*input_json_ptr)["name"]).asString();
  this->fhandle = ((*input_json_ptr)["fhandle"]).asString();

  return true;
}

Directory::Directory
(std::string core_arg_host_url, std::string core_arg_owner_vsID,
 std::string core_arg_class_id, std::string core_arg_object_id)
  : Core { core_arg_host_url, core_arg_owner_vsID,
    core_arg_class_id, core_arg_object_id }
{
  std::cout << "a shadow has been created" << std::endl;
  this->dirent_vector_ptr = NULL;
}

Directory::Directory
(std::string core_arg_host_url, std::string core_arg_owner_vsID,
 std::string core_arg_class_id, std::string core_arg_object_id,
 std::string arg_name, std::string arg_fhandle)
  : Core { core_arg_host_url, core_arg_owner_vsID,
    core_arg_class_id, core_arg_object_id }
{
  this->dirent_vector_ptr = new std::vector<Dirent *>();
  this->name = arg_name;
  this->fhandle = arg_fhandle;
}

Json::Value
Directory::ObtainChunkURL
(std::string arg_name, std::string arg_fhandle, std::string arg_chunk_index)
{
  Json::Value result;
  result["primary"]      = (this->the_chunk).chunk_url_primary;
  result["secondary_A"]  = (this->the_chunk).chunk_url_secondary_A;
  result["secondary_B"]  = (this->the_chunk).chunk_url_secondary_B;
  return result;
}

Json::Value
Directory::LookUp
(std::string arg_dir_fhandle, std::string arg_name)
{
  int i;
  int flag = 0;
  Json::Value result;

  if (arg_dir_fhandle == this->fhandle)
    {
      for (i = 0; i < (this->dirent_vector_ptr)->size(); i++)
	{
	  if (((*(this->dirent_vector_ptr))[i])->name == arg_name)
	    {
	      result["fhandle"] = ((*(this->dirent_vector_ptr))[i])->fhandle;
	      flag = 1;
	    }
	}
      if (flag == 0)
	{
	  result["status"] = "NFSERR_NOENT";
	}
      else
	{
	  result["status"] = "NFS_OK";
	}
    }
  else
    {
      result["status"] = "NFSERR_STALE";
    }
  return result;
}

Json::Value
Directory::Create
(std::string arg_dir_fhandle, std::string arg_name, std::string arg_sattr)
{
  int i;
  Json::Value result;

  if (arg_dir_fhandle == this->fhandle)
    {
      int flag = 0;
      for (i = 0; i < (this->dirent_vector_ptr)->size(); i++)
	{
	  if (((*(this->dirent_vector_ptr))[i])->name == arg_name)
	    {
	      flag = 1;
	    }
	}
      if (flag == 0)
	{
	  char fhandle_buf[256];
	  bzero(fhandle_buf, 256);
	  sprintf(fhandle_buf, "%ld%ld", random(), random());
	  std::string new_fhandle { fhandle_buf };

	  Dirent *dirent_ptr = new Dirent(arg_name, new_fhandle);
	  (*(this->dirent_vector_ptr)).push_back(dirent_ptr);
	  result["status"] = "NFS_OK";
	}
      else
	{
	  result["status"] = "NFSERR_ACCES";
	}
    }
  else
    {
      result["status"] = "NFSERR_STALE";
    }
  return result;
}

Json::Value *
Directory::dumpJ()
{
  Json::Value * result_ptr = new Json::Value();

  if (this->name != "")
    {
      (*result_ptr)["name"] = this->name;
    }

  if (this->fhandle != "")
    {
      (*result_ptr)["fhandle"] = this->fhandle;
    }

  int i;
  if ((this->dirent_vector_ptr != NULL) && 
      ((this->dirent_vector_ptr)->size() > 0))
    {
      Json::Value json_dirents;
      Json::Value json_dirents_array;

      for (i = 0; i < (this->dirent_vector_ptr)->size(); i++)
	{
	  Json::Value * dumpjv_ptr = ((*(this->dirent_vector_ptr))[i])->dumpJ();
	  json_dirents[i] = (*dumpjv_ptr);
	  delete dumpjv_ptr;
	}
      json_dirents_array["data"] = json_dirents;
      json_dirents_array["count"] = ((int) (*(this->dirent_vector_ptr)).size());
      (*result_ptr)["dirents"] = json_dirents_array;
    }

  std::cout << (*result_ptr).toStyledString() << std::endl;
  return result_ptr;
}

bool
Directory::Jdump(Json::Value *input_json_ptr)
{
  if ((input_json_ptr == NULL) ||
      ((*input_json_ptr).isNull() == true) ||
      ((*input_json_ptr).isObject() != true))
    {
      return false;
    }

  if ((((*input_json_ptr)["name"]).isNull() == true) ||
      (((*input_json_ptr)["fhandle"]).isNull() == true) ||
      (((*input_json_ptr)["name"]).isString() != true) ||
      (((*input_json_ptr)["fhandle"]).isString() != true))
    {
      return false;
    }

  this->name    = ((*input_json_ptr)["name"]).asString();
  this->fhandle = ((*input_json_ptr)["fhandle"]).asString();

  // check if there is any valid directory entry
  if ((((*input_json_ptr)["dirents"]).isNull() == false) &&
      (((*input_json_ptr)["dirents"]).isObject() == true) &&
      (((*input_json_ptr)["dirents"]["data"]).isNull() == false) &&
      (((*input_json_ptr)["dirents"]["data"]).isArray() == true) &&
      (((*input_json_ptr)["dirents"]["data"]).size() > 0))
    {
      int i;
      for (i = 0; i < ((*input_json_ptr)["dirents"]["data"]).size(); i++)
        {
	  Json::Value l_jv_dirent = (*input_json_ptr)["dirents"]["data"][i];
          Dirent *l_dirent_ptr = new Dirent();
          bool rc = l_dirent_ptr->Jdump(&(l_jv_dirent));
          if (rc == true)
            {
              // now check if the dirent already exist
              int flag_dr = 0;
              if (this->dirent_vector_ptr != NULL)
                {
		  std::vector<Dirent *>::iterator my_it_dr;
                  for (my_it_dr = (*(this->dirent_vector_ptr)).begin();
                       my_it_dr < (*(this->dirent_vector_ptr)).end(); my_it_dr++)
                    {
                      if (((*my_it_dr)->name) == (l_dirent_ptr->name))
                        {
                          // this is a duplicated dirent (name must be different even inode the same
                          flag_dr = 1;
                        }
		    }
		}
	      else
		{
		  // create this->dirent_vector_ptr
		  this->dirent_vector_ptr = new std::vector<Dirent *>();
		}

	      if (flag_dr == 0)
		{
		  (*(this->dirent_vector_ptr)).push_back(l_dirent_ptr);
		}
	      else
		{
		  delete l_dirent_ptr;
		}
	    }
	}
    }

  return true;
}

