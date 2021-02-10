			//sprintf = StringCchPrintf
			//strcpy = StringCchCopy
			
			//--------------------------------------------------------------------------------------
			// Returns pointer to static file search buffer
			//--------------------------------------------------------------------------------------
			CHAR* FileSearchPath(){
			    static CHAR s_strFileSearchPath[MAX_PATH] = "";//{0};
			    return s_strFileSearchPath;
			
			}  
			
			//--------------------------------------------------------------------------------------
			LPCSTR GetFileSearchPath(){
			    return FileSearchPath();
			}
			
			
			//--------------------------------------------------------------------------------------
			HRESULT SetFileSearchPath( LPCSTR strPath ){
			    HRESULT hr;
			
			    char* s_strSearchPath = FileSearchPath();
			
			    hr = strcpy( s_strSearchPath, MAX_PATH, strPath );   
			    if( SUCCEEDED(hr) ) {
				// append slash if needed
				unsigned int ch;
				hr = StringCchLength( s_strSearchPath, MAX_PATH, &ch );
				if( (SUCCEEDED(hr)) && (&s_strSearchPath[ch-1] != "\\"))
				{
				    hr = StringCchCat( s_strSearchPath, MAX_PATH, "\\" );
				}
			    }
			
			    return hr;
			}
			
			
			//--------------------------------------------------------------------------------------
			// Tries to find the location of a SDK file file
			//       cchDest is the size in CHARs of strDestPath.  Be careful not to 
			//       pass in sizeof(strDest) on UNICODE builds.
			//--------------------------------------------------------------------------------------
			HRESULT FindDXSDKFileFileCch( CHAR* strDestPath, int cchDest, LPCSTR strFilename ){
			    bool bFound;
			    CHAR strSearchFor[MAX_PATH];
			    
			   // if( NULL==strFilename || strFilename[0] == "\0" || NULL==strDestPath || cchDest < 10 )
			       // return E_INVALIDARG;
			
			    // Get the exe name, and exe path
			
				
				char strExePath[MAX_PATH];// = "";//{0};
			    char strExeName[MAX_PATH];// = "";//{0};
			    char* strLastSlash = NULL;
			    GetModuleFileName( NULL, strExePath, MAX_PATH );
			    strExePath[MAX_PATH-1]= (char)"\0"; //0;
			    strLastSlash = strrchr( strExePath, (char)"\\" );
			    if( strLastSlash )
			    {
				strcpy_s( strExeName, MAX_PATH, &strLastSlash[1] );
			
				// Chop the exe name from the exe path
				*strLastSlash = (char)"\0";
			
				// Chop the .exe from the exe name
				strLastSlash = strchr( strExeName, (char)"." );
				if( strLastSlash )
				    *strLastSlash = (char)"\0";
			    }
			
			    // Typical directories:
			    //      .\
			    //      ..\
			    //      ..\..\
			    //      %EXE_DIR%\
			    //      %EXE_DIR%\..\
			    //      %EXE_DIR%\..\..\
			    //      %EXE_DIR%\..\%EXE_NAME%
			    //      %EXE_DIR%\..\..\%EXE_NAME%
			
			    // Typical directory search
			    bFound = FindFileSearchTypicalDirs( strDestPath, cchDest, strFilename, strExePath, strExeName );
			    if( bFound )
				return S_OK;
			
			    // Typical directory search again, but also look in a subdir called "\file\" 
			    sprintf( strSearchFor, MAX_PATH, "file\\%s", strFilename ); 
			    bFound = FindFileSearchTypicalDirs( strDestPath, cchDest, strSearchFor, strExePath, strExeName );
			    if( bFound )
				return S_OK;
			
			    CHAR strLeafName[MAX_PATH] = "";//{0};
			
			    // Search all parent directories starting at .\ and using strFilename as the leaf name
			    strcpy( strLeafName, MAX_PATH, strFilename ); 
			    bFound = FindFileSearchParentDirs( strDestPath, cchDest, ".", strLeafName );
			    if( bFound )
				return S_OK;
			
			    // Search all parent directories starting at the exe's dir and using strFilename as the leaf name
			    bFound = FindFileSearchParentDirs( strDestPath, cchDest, strExePath, strLeafName );
			    if( bFound )
				return S_OK;
			
			    // Search all parent directories starting at .\ and using "file\strFilename" as the leaf name
			    sprintf( strLeafName, MAX_PATH, "file\\%s", strFilename ); 
			    bFound = FindFileSearchParentDirs( strDestPath, cchDest, ".", strLeafName );
			    if( bFound )
				return S_OK;
			
			    // Search all parent directories starting at the exe's dir and using "file\strFilename" as the leaf name
			    bFound = FindFileSearchParentDirs( strDestPath, cchDest, strExePath, strLeafName );
			    if( bFound )
				return S_OK;
			
			    // On failure, return the file as the path but also return an error code
			    strcpy( strDestPath, cchDest, strFilename );
			
			    return DITTOTPU_ERROR;
			}
			
			
			//--------------------------------------------------------------------------------------
			// Search a set of typical directories
			//--------------------------------------------------------------------------------------
			bool FindFileSearchTypicalDirs( CHAR* strSearchPath, int cchSearch, LPCSTR strLeaf, CHAR* strExePath, CHAR* strExeName ){
			    // Typical directories:
			    //      .\
			    //      ..\
			    //      ..\..\
			    //      %EXE_DIR%\
			    //      %EXE_DIR%\..\
			    //      %EXE_DIR%\..\..\
			    //      %EXE_DIR%\..\%EXE_NAME%
			    //      %EXE_DIR%\..\..\%EXE_NAME%
			    //      DXSDK file path
			
			    // Search in .\  
			    strcpy( strSearchPath, cchSearch, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in ..\  
			    sprintf( strSearchPath, cchSearch, "..\\%s", strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in ..\..\ 
			    sprintf( strSearchPath, cchSearch, "..\\..\\%s", strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in ..\..\ 
			    sprintf( strSearchPath, cchSearch, "..\\..\\%s", strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in the %EXE_DIR%\ 
			    sprintf( strSearchPath, cchSearch, "%s\\%s", strExePath, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in the %EXE_DIR%\..\ 
			    sprintf( strSearchPath, cchSearch, "%s\\..\\%s", strExePath, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in the %EXE_DIR%\..\..\ 
			    sprintf( strSearchPath, cchSearch, "%s\\..\\..\\%s", strExePath, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in "%EXE_DIR%\..\%EXE_NAME%\".  This matches the DirectX SDK layout
			    sprintf( strSearchPath, cchSearch, "%s\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in "%EXE_DIR%\..\..\%EXE_NAME%\".  This matches the DirectX SDK layout
			    sprintf( strSearchPath, cchSearch, "%s\\..\\..\\%s\\%s", strExePath, strExeName, strLeaf ); 
			    if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				return true;
			
			    // Search in file search dir 
			    CHAR* s_strSearchPath = FileSearchPath();
			    if( s_strSearchPath[0] != 0 )
			    {
				sprintf( strSearchPath, cchSearch, "%s%s", s_strSearchPath, strLeaf ); 
				if( GetFileAttributes( strSearchPath ) != 0xFFFFFFFF )
				    return true;
			    }
			
			    return false;
			}
			
			
			
			//--------------------------------------------------------------------------------------
			// Search parent directories starting at strStartAt, and appending strLeafName
			// at each parent directory.  It stops at the root directory.
			//--------------------------------------------------------------------------------------
			bool FindFileSearchParentDirs( CHAR* strSearchPath, int cchSearch, CHAR* strStartAt, CHAR* strLeafName ){
			    CHAR strFullPath[MAX_PATH] = "";//{0};
			    CHAR strFullFileName[MAX_PATH] = "";//{0};
			    CHAR strSearch[MAX_PATH] = "";//{0};
			    CHAR* strFilePart = NULL;
			
			    GetFullPathName( strStartAt, MAX_PATH, strFullPath, &strFilePart );
			    if( strFilePart == NULL )
				return false;
			   
			    while( strFilePart != NULL && strFilePart != "\0" )
			    {
				sprintf( strFullFileName, MAX_PATH, "%s\\%s", strFullPath, strLeafName ); 
				if( GetFileAttributes( strFullFileName ) != 0xFFFFFFFF )
				{
				    strcpy( strSearchPath, cchSearch, strFullFileName ); 
				    return true;
				}
			
				sprintf( strSearch, MAX_PATH, "%s\\..", strFullPath ); 
				GetFullPathName( strSearch, MAX_PATH, strFullPath, &strFilePart );
			    }
			
			    return false;
			}

