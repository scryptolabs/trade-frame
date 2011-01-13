/************************************************************************
 * Copyright(c) 2010, One Unified. All rights reserved.                 *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *
 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/

// LibSqlite/Actions.cpp

#include "Actions.h"

namespace ou {
namespace db {
namespace sqlite {

const char* Action_Assemble_TableDef::FieldType( char key ) {
  return "TINYINT";
}

const char* Action_Assemble_TableDef::FieldType( bool key ) {
  return "TINYINT";
}

const char* Action_Assemble_TableDef::FieldType( boost::int64_t key ) {
  return "INT8"; 
}

const char* Action_Assemble_TableDef::FieldType( boost::int32_t key ) {
  return "BIGINT";
}

const char* Action_Assemble_TableDef::FieldType( boost::int16_t key ) {
  return "SMALLINT";
}

const char* Action_Assemble_TableDef::FieldType( boost::int8_t key ) {
  return "TINYINT";
}

const char* Action_Assemble_TableDef::FieldType( std::string& key ) {
  return "TEXT";
}

const char* Action_Assemble_TableDef::FieldType( double key ) {
  return "DOUBLE";
}

// don't use julian as ptime has no representation earlier than 1400 AD
const char* Action_Assemble_TableDef::FieldType( boost::posix_time::ptime& key ) { 
  return "TEXT";
}


template<>
const char* FieldType2<char>( void ) { return "TINYINT"; };

template<> // don't use julian as ptime has no representation earlier than 1400 AD
const char* FieldType2<boost::posix_time::ptime>( void ) { return "TEXT"; }

template<>
const char* FieldType2<bool>( void ) { return "TINYINT"; }

template<>
const char* FieldType2<boost::int64_t>( void ) { return "INT8"; }

template<>
const char* FieldType2<boost::int32_t>( void ) { return "BIGINT"; }

template<>
const char* FieldType2<boost::int16_t>( void ) { return "SMALLINT"; }

template<>
const char* FieldType2<boost::int8_t>( void ) { return "TINYINT"; }

template<>
const char* FieldType2<std::string>( void ) { return "TEXT"; }

template<>
const char* FieldType2<double>( void ) { return "DOUBLE"; }




} // sqlite
} // db
} // ou