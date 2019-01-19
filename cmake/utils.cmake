function(map_append_value_to_key map_var key value)
	if("${${map_var}}" STREQUAL "")
		set("${map_var}" "MAP")
		set("${map_var}_KEYS" "")
		set("${map_var}_VALUES" "")
		set("${map_var}" "${${map_var}}" PARENT_SCOPE)
		set("${map_var}_KEYS" "${${map_var}_KEYS}" PARENT_SCOPE)
		set("${map_var}_VALUES" "${${map_var}_VALUES}" PARENT_SCOPE)
	endif()

	list(FIND "${map_var}_KEYS" "${key}" KEY_INDEX)

	if("${KEY_INDEX}" EQUAL -1)
		if("${${map_var}_KEYS}" STREQUAL "")
			set("${map_var}_KEYS" "${key}")
		else()
			set("${map_var}_KEYS" "${${map_var}_KEYS};${key}")
		endif()

		set("${map_var}_VALUES_${key}" "")
	endif()

	list(APPEND "${map_var}_VALUES_${key}" "${value}")

	set("${map_var}_KEYS" "${${map_var}_KEYS}" PARENT_SCOPE)
	set("${map_var}_VALUES_${key}" "${${map_var}_VALUES_${key}}" PARENT_SCOPE)
endfunction()

function(map_get_keys map_var res_var)
	set("${res_var}" "${${map_var}_KEYS}" PARENT_SCOPE)
endfunction()

function(map_get_values_for_key map_var key res_var)
	set("${res_var}" "${${map_var}_VALUES_${key}}" PARENT_SCOPE)
endfunction()

function(make_fs_source_group_for_target target)
	get_target_property(TARGET_SOURCES "${target}" SOURCES)

	foreach(TARGET_SOURCE ${TARGET_SOURCES})
		get_filename_component(TARGET_SOURCE_DIR "${TARGET_SOURCE}" DIRECTORY)
		
		if("${TARGET_SOURCE_DIR}" STREQUAL "")
			set(TARGET_SOURCE_DIR "misc")
		endif()
		string(REPLACE "/" "\\" TARGET_SOURCE_DIR ${TARGET_SOURCE_DIR})

		map_append_value_to_key(SOURCE_MAP "${TARGET_SOURCE_DIR}" "${TARGET_SOURCE}")
	endforeach(TARGET_SOURCE)

	map_get_keys(SOURCE_MAP MAP_KEYS)
	foreach(KEY ${MAP_KEYS})
		map_get_values_for_key(SOURCE_MAP "${KEY}" MAP_VALUES)
#		message(STATUS "Files\\${KEY}: ${MAP_VALUES}")
		source_group("Files\\${KEY}" FILES ${MAP_VALUES})
	endforeach(KEY)
endfunction()