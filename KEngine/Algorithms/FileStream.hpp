#pragma once

#include <fstream>
#include "Algor.hpp"
#include "../Structures/Settings.hpp"


namespace ke
{

	/// <summary>
	/// KEngie Filestream is an object based on std::fstream that can help you using files.
	/// You can use it for reading or saving many things.
	/// </summary>
	class FileStream
	{
	public:

		/// <summary>
		/// Filestream default constructor
		/// </summary>
		FileStream();

		
		////////////////


		/// <summary>
		/// Filestream constructor
		/// </summary>
		/// <param name="filename">path to your file</param>
		/// <param name="mode">std::fstream mode (for example std::ios::in | std::ios::binary etc...)</param>
		/// <param name="prot">std::fstream protection</param>
		FileStream(const std::string& filename, std::ios_base::openmode mode, int prot = std::ios::_Default_open_prot);


		/// <summary>
		/// Filestream destructor - closes file
		/// </summary>
		~FileStream();


		////////////////////////////////


		/// <summary>
		/// creates file that does not exist (e.g. binary files), use once
		/// </summary>
		/// <param name="filename">where you want to make the file</param>
		void createFile(const std::string& filename);


		/// <summary>
		/// sets name (for error handling)
		/// </summary>
		/// <param name="name">displayed name</param>
		void setFileName(const std::string& name);


		/// <summary>
		/// returns custom name (for error handling handling)
		/// </summary>
		/// <returns>custom file name</returns>
		std::string getFileName() const;


		////////////////////////////////


		/// <summary>
		/// opens file, use rather with empty constructor
		/// </summary>
		/// <param name="filename">path to your file</param>
		/// <param name="mode">std::fstream mode (for example std::ios::in | std::ios::binary etc...)</param>
		/// <param name="prot">std::fstream protection</param>
		/// <returns>if opened successfully - true</returns>
		bool open(const std::string& filename, std::ios_base::openmode mode, int prot = std::ios::_Default_open_prot);


		/// <summary>
		/// closes the file
		/// </summary>
		void close();



		////////////////////////////////////////////////////////////////



		/// <summary>
		/// std::fstream getline function
		/// </summary>
		/// <param name="_string">string you want to save message</param>
		/// <param name="ending_char">character ending std::getline function</param>
		/// <returns></returns>
		bool getline(std::string& _string, char ending_char = '\n');


		////////////////////////////////


		/// <summary>
		/// reads variable from txt file
		/// </summary>
		/// <typeparam name="T">variable / string, could be anything</typeparam>
		/// <param name="variable"></param>
		/// <returns>if opened successfully - true</returns>
		template <typename T>
		inline bool textRead(T& variable);


		/// <summary>
		/// writes variable to txt file
		/// </summary>
		/// <typeparam name="T">variable / string, could be anything</typeparam>
		/// <param name="variable"></param>
		/// <returns>if opened successfully - true</returns>
		template <typename T>
		inline bool textWrite(const T& variable);


		////////////////////////////////


		/// <summary>
		/// reads string from binary file
		/// </summary>
		/// <param name="_string"></param>
		/// <returns>if opened successfully - true</returns>
		bool binRead(std::string& _string);


		/// <summary>
		/// writes string to binary file
		/// </summary>
		/// <param name="_string"></param>
		/// <returns>if opened successfully - true</returns>
		bool binWrite(const std::string& _string);




		/// <summary>
		/// reads string from binary file
		/// </summary>
		/// <param name="_string"></param>
		/// <returns>if opened successfully - true</returns>
		bool binRead(char* _string);


		/// <summary>
		/// writes string to binary file
		/// </summary>
		/// <param name="_string"></param>
		/// <returns>if opened successfully - true</returns>
		bool binWrite(const char* _string);


		////////////////////////////////


		/// <summary>
		/// reads variable from binary file
		/// </summary>
		/// <typeparam name="T">single variable</typeparam>
		/// <param name="variable"></param>
		/// <returns>if opened successfully - true</returns>
		template <typename T>
		inline bool binRead(T& variable);


		/// <summary>
		/// writes variable to binary file
		/// </summary>
		/// <typeparam name="T">siangle variable</typeparam>
		/// <param name="variable"></param>
		/// <returns>if opened successfully - true</returns>
		template <typename T>
		inline bool binWrite(const T& variable);



		////////////////////////////////////////////////////////////////////////////////



		/// <summary>
		/// std::fstream seekg() function
		/// </summary>
		/// <param name="s_posistion">seekg position</param>
		void seekg(std::streampos s_posistion);


		/// <summary>
		/// std::fstram seekg() function
		/// </summary>
		/// <param name="s_off">offset</param>
		/// <param name="way">way</param>
		void seekg(std::streamoff s_off, std::ios_base::seekdir way);


		////////////////////////////////


		/// <summary>
		/// std::fstream seekp() function
		/// </summary>
		/// <param name="s_posistion">position</param>
		void seekp(std::streampos s_posistion);


		/// <summary>
		/// std::fstream seekp() function
		/// </summary>
		/// <param name="s_off">offset</param>
		/// <param name="way">way</param>
		void seekp(std::streamoff s_off, std::ios_base::seekdir way);



		////////////////////////////////////////////////////////////////////////////////



		/// <summary>
		/// returns std::fstream class used in ke::FileStream
		/// </summary>
		/// <returns></returns>
		std::fstream* getFStream();


		////////////////////////////////


		/// <summary>
		/// checks if file is opened
		/// </summary>
		/// <returns>if file is loaded - true</returns>
		bool loaded() const;

		

		////////////////////////////////////////////////////////////////////////////////



		/// <summary>
		/// '\n' character, use it if you want to make new line in txt file  (! not necessary right now)
		/// </summary>
		static const char newline = '\n';


		/// <summary>
		/// ' ' character, use it if you want to make space in txt file  (! not necessary right now)
		/// </summary>
		static const char space = ' ';

	private:

		std::fstream m_file_stream;	// fstream object
		std::string m_file_name;	// custom file name
									
		bool m_loaded;				// has filestream been loaded?

	};




	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	// inline and teplate definitions


	template <typename T>
	inline bool FileStream::textRead(T& variable)
	{
		bool ret_val = true;

		if (m_file_stream.eof())
		{
			throw_error("FileStream::textRead(T)", "\"" + m_file_name + " is incomplete - reached end of file", "WARNING");
			ret_val = false;
		}

		if (!(m_file_stream >> variable))
		{
			throw_error("FileStream::textRead(T)", "could not read from \"" + m_file_name + "\"", "ERROR");
			ret_val = false;
		}

		return ret_val;
	}

	template <typename T>
	inline bool FileStream::textWrite(const T& variable)
	{
		if (!(m_file_stream << variable))
		{
			throw_error("FileStream::textWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
			return false;
		}

		return true;
	}



	////////////////////////////////



	template <typename T>
	inline bool FileStream::binRead(T& variable)
	{
		bool ret_val = true;

		if (m_file_stream.eof())
		{
			throw_error("FileStream::binRead(T)", "\"" + m_file_name + " is incomplete - reached end of file", "WARNING");
			ret_val = false;
		}

		if (!(m_file_stream.read(reinterpret_cast<char*>(&variable), sizeof(variable))))
		{
			throw_error("FileStream::binRead(T)", "could not read from \"" + m_file_name + "\"", "ERROR");
			ret_val = false;
		}

		return ret_val;
	}

	template <typename T>
	inline bool FileStream::binWrite(const T& variable)
	{
		T buff = variable;
		if (!(m_file_stream.write(reinterpret_cast<char*>(&buff), sizeof(variable))))
		{
			throw_error("FileStream::binWrite(T)", "could not write to \"" + m_file_name + "\"", "ERROR");
			return false;
		}

		return true;
	}

} // namespace ke