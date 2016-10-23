#include "header.h"

result_set_t dirContents(string dirName)
{
	fs::path dir(dirName);
	result_set_t result_set;
	if(exists(dir))
	{
		fs::directory_iterator end;
		for( fs::directory_iterator iter(dir) ; iter != end ; ++iter )
		{
			if ( !is_directory( *iter ) )
			{
				result_set.insert(
					result_set_t::value_type(
						fs::last_write_time(iter->path()), *iter));
			}
		}
	}
	return result_set;
}
