#include "SoftwareDefenitions.h"

void TestFile(HANDLE& File1) {

	char BufferFileName[FileBufferSize];
	GetFinalPathNameByHandleA(File1, BufferFileName, FileBufferSize, FILE_NAME_NORMALIZED);

	memset(&FileBuffer[0], 0, sizeof(FileBuffer));

	std::string wsBFN (BufferFileName);
	string CheckName(wsBFN.begin(), wsBFN.end());
	CheckName.erase(0, CheckName.rfind("\\") + 1);

	::FileName = CheckName.c_str();

	ReadFile(File1, FileBuffer, FileBufferSize, &bytesInterated, NULL);

	string StrFileBuffer1 = string(FileBuffer);
	std::istringstream IsStrFileBuffer1(StrFileBuffer1);

	memset(&FileBuffer[0], 0, sizeof(FileBuffer));

	WIN32_FIND_DATAA wfd;
	HANDLE hFind = FindFirstFileA(((string)(TestSuperPath + "reports\\*")).c_str(), &wfd);

	string StrSeek1;
	string StrSeek2;
	string StrResult = "";

	if (INVALID_HANDLE_VALUE != hFind) {

		int CountDo = 0;
		do {

			if (CountDo++ > 1) {

				if (CheckName != wfd.cFileName) {

					string nameFile = TestSuperPath + "reports\\";
					nameFile += wfd.cFileName;

					string TestFileName = (string)wfd.cFileName;
					string TFN = TestFileName.substr(TestFileName.rfind(".") + 1, TestFileName.length());

					if (TFN == "txt") {

						HANDLE File2;
						File2 = CreateFileA(nameFile.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						ReadFile(File2, FileBuffer, FileBufferSize, &bytesInterated, NULL);

						std::istringstream IsStrFileBuffer2((string)FileBuffer);

						memset(&FileBuffer[0], 0, sizeof(FileBuffer));

						double Match = 0;

						IsStrFileBuffer1.clear();
						IsStrFileBuffer1.seekg(0, std::ios::beg);

						while (std::getline(IsStrFileBuffer1, StrSeek1)) {

							std::getline(IsStrFileBuffer2, StrSeek2);

							if ((StrSeek1.find("ASCII")) && ((Match / 3 >= 0.7))) {

								StrSeek1.erase(0, StrSeek1.rfind("-") + 2);
								StrSeek2.erase(0, StrSeek2.rfind("-") + 2);

								int percent;

								if (std::stoi(StrSeek1) >= std::stoi(StrSeek2)) {

									percent = std::stold(StrSeek2) / std::stold(StrSeek1) * 100;

								}

								else {

									percent = std::stold(StrSeek1) / std::stold(StrSeek2) * 100;

								}

								if (percent >= ::percent) {

									StrResult += "Файл совпадает по ASCII коду с";
									StrResult += "\r\n";
									StrResult += wfd.cFileName;
									StrResult += "\r\n";
									StrResult += "на " + std::to_string((int)percent) + "%";
									StrResult += "\r\n\r\n";

									NameFileInComboBox[NFInCB_i++] = wfd.cFileName;

								}

							}

							else {

								StrSeek1.erase(0, StrSeek1.find("-") + 2);
								StrSeek2.erase(0, StrSeek2.find("-") + 2);

								if (std::stoi(StrSeek2) != 0) {

									double val = 0;

									if (std::stoi(StrSeek1) >= std::stoi(StrSeek2)) {
									
										val = (double)(std::stoi(StrSeek2) / std::stoi(StrSeek1));
									
									}

									else {
									
										val = (double)(std::stoi(StrSeek1) / std::stoi(StrSeek2));

									
									}

									Match += val;

								}

								else if ((std::stoi(StrSeek2) == 0) && (std::stoi(StrSeek1) < 4)) {
								
									Match += (4 - std::stoi(StrSeek1)) / 4;
								
								}

							}

						}

						CloseHandle(File2);

					}

				}

			}

		} while (NULL != FindNextFileA(hFind, &wfd));

		if (StrResult == "") {

			StrResult = "Совпадения не найдены!";

		}

		SetWindowTextA(Set, StrResult.c_str());

		FindClose(hFind);

	}

}

void ReadFile(LPSTR path) {

	while (NFInCB_i != -1) {
	
		NameFileInComboBox[NFInCB_i--] = '\0';

	}
	NFInCB_i++;

	if (TestSuperPath == "") {

		SetWindowTextA(Set, "Ошибка тестирования, не введен путь до папки с работами. Настройте путь в \"Настройка путей\"");

	}

	else {

		HANDLE FileToLoad = CreateFileA(path, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		memset(&FileBuffer[0], 0, sizeof(FileBuffer));

		ReadFile(FileToLoad, FileBuffer, FileBufferSize, &bytesInterated, NULL);

		string nameFile = path;

		nameFile[nameFile.rfind(".")] = '_';
		nameFile.erase(0, 3);

		if (nameFile.find("ПМИ") != -1) {

			nameFile.erase(0, nameFile.find("ПМИ"));

		}

		else if (nameFile.find("АИС") != -1) {

			nameFile.erase(0, nameFile.find("АИС"));

		}

		else if (nameFile.find("НТ") != -1) {

			nameFile.erase(0, nameFile.find("НТ"));

		}

		while (nameFile.find("\\") != -1) {

			nameFile[nameFile.find("\\")] = '_';

		}

		string FToS = TestSuperPath + "codes\\" + nameFile + ".txt";
		HANDLE FileToSave = CreateFileA(FToS.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(FileToSave, FileBuffer, FileBufferSize, &bytesInterated, NULL);
		CloseHandle(FileToSave);
		
		int CountWhile = 0;
		int CountFor = 0;
		int CountIf = 0;
		int ASCIISizeFile = 0;

		string StrSeek;

		std::istringstream IsStrFileBuffer((string)FileBuffer);
		memset(&FileBuffer[0], 0, sizeof(FileBuffer));
		while (std::getline(IsStrFileBuffer, StrSeek)) {

			if (StrSeek.find("//") != -1) {

				if (StrSeek.find("/") == 0) {

					continue;

				}

				StrSeek.erase(StrSeek.find("//"), StrSeek.length());

			}

			else if (StrSeek.find("/*") != -1) {

				do {

					if (StrSeek.find("*/") != -1) {

						if (StrSeek.find("/*") == -1) {
						
							std::getline(IsStrFileBuffer, StrSeek);
						
						}

						break;

					}

				} while (std::getline(IsStrFileBuffer, StrSeek));

			}

			else {

				if ((StrSeek.find("while (") != -1) || (StrSeek.find("while(") != -1)) {

					if ((StrSeek.find(" while (") != -1) || (StrSeek.find(" while(") != -1) || (StrSeek.find("\twhile (") != -1) || (StrSeek.find("\twhile(") != -1) || (StrSeek.find("w") == 0)) {

						CountWhile++;

					}

				}

				if ((StrSeek.find("for (") != -1) || (StrSeek.find("for(") != -1)) {

					if ((StrSeek.find(" for (") != -1) || (StrSeek.find(" for(") != -1) || (StrSeek.find("\tfor (") != -1) || (StrSeek.find("\tfor(") != -1) || (StrSeek.find("f") == 0)) {

						CountFor++;

					}

				}

				if ((StrSeek.find("if (") != -1) || (StrSeek.find("if(") != -1)) {

					if ((StrSeek.find(" if (") != -1) || (StrSeek.find(" if(") != -1) || (StrSeek.find("\tif (") != -1) || (StrSeek.find("\tif(") != -1) || (StrSeek.find("i") == 0)) {

						CountIf++;

					}

				}

				for (int i = 0; i < (int)StrSeek.length(); i++) {

					ASCIISizeFile += (int)StrSeek[i];

				}

			}

		}

		CloseHandle(FileToLoad);

		string StrResult;

		StrResult += "Количествго циклов while - " + std::to_string(CountWhile) + "\r\n";
		StrResult += "Количествго циклов for - " + std::to_string(CountFor) + "\r\n";
		StrResult += "Количествго условий if - " + std::to_string(CountIf) + "\r\n";
		StrResult += "Сумма ASCII - " + std::to_string(ASCIISizeFile);

		string TSPtmp = TestSuperPath + "reports";

		TSPtmp.erase(TSPtmp.rfind("\\"), TSPtmp.length());

		string nameF = TSPtmp + "\\" + nameFile + ".txt";

		HANDLE FileToTest = CreateFileA(nameF.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(FileToTest, StrResult.c_str(), StrResult.length() + 1, &bytesInterated, NULL);
		CloseHandle(FileToTest);

		FileToTest = CreateFileA(nameF.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		TestFile(FileToTest);
		CloseHandle(FileToTest);

		DeleteFileA(nameF.c_str());

		nameF = TestSuperPath + "reports\\" + nameFile + ".txt";

		FileToTest = CreateFileA(nameF.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(FileToTest, StrResult.c_str(), StrResult.length() + 1, &bytesInterated, NULL);
		CloseHandle(FileToTest);

	}

}