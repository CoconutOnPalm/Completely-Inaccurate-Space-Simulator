#include "Algor.hpp"

namespace ke
{
	namespace protect
	{

		std::string Encrypt(const std::string& decoded)
		{
			int shift_val = Random::Int(1, 128);

			std::string encrypted;
			encrypted += shift_val;

			for (unsigned int i = 0; i < decoded.size(); i++)
				encrypted += (decoded[i] + shift_val);

			return encrypted;
		}

		std::string Decode(const std::string& encrypted)
		{
			int shift_val = encrypted.front();

			std::string decoded;

			for (unsigned int i = 1; i < encrypted.size(); i++)
				decoded += (encrypted[i] - shift_val);

			return decoded;
		}


		////////////////////////////////


		std::string CustomEncrypt(const std::string& decoded, int key)
		{
			std::string encrypted;

			for (unsigned int i = 0; i < decoded.size(); i++)
				encrypted += (decoded[i] + key);

			return encrypted;
		}

		std::string CustomDecode(const std::string& encrypted, int key)
		{
			std::string decoded;

			for (unsigned int i = 0; i < encrypted.size(); i++)
				decoded += (encrypted[i] - key);

			return decoded;
		}


		////////////////////////////////


		std::string AdvancedCustomEncrypt(const std::string& decoded, std::string key)
		{
			int key_start_size = key.size();
			for (int i = 0; key.size() < decoded.size(); i++)
			{
				if (i >= key_start_size) i = 0;
				key += key[i];
			}

			std::string encrypted;

			for (unsigned int i = 0; i < decoded.size(); i++)
				encrypted += (decoded[i] + key[i] - '0');

			return encrypted;
		}


		std::string AdvancedCustomDecode(const std::string& encrypted, std::string key)
		{
			int key_start_size = key.size();
			for (int i = 0; key.size() < encrypted.size(); i++)
			{
				if (i >= key_start_size) i = 0;
				key += key[i];
			}

			std::string decoded;

			for (unsigned int i = 0; i < encrypted.size(); i++)
				decoded += (encrypted[i] - key[i] + '0');

			return decoded;
		}

	} // namespace protect

} // namespace ke