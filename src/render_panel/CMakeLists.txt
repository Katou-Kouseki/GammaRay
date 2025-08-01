set(PANEL_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/network/http_handler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network/ws_panel_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network/udp_broadcaster.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network/gr_service_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network/ws_sig_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/network/render_api.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/database/db_game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/db_game_operator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/gr_database.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/visit_record.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/visit_record_operator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/file_transfer_record.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/file_transfer_record_operator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/stream_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/database/stream_db_operator.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_base.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_settings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_server_status.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_security_internals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_general.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_about_me.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_network.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_plugins.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_plugin_item_widget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_security.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/game_info_preview.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/rn_app.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/rn_empty.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/stat_chart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/qt_circle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/qt_vertical.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/add_game_panel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_profile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/stat_capture_info_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/input_safety_pwd_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_security_visitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_security_file_transfer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_security_visitor_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/st_security_file_transfer_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/tab_profile_device_item.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/security_password_checker.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/gr_application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_workspace.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_settings.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_statistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_system_monitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_resources.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_render_controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_run_game_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_running_pipe.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_account_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_connected_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gr_render_msg_processor.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/transfer/file_transfer.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/devices/app_stream_list.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/create_stream_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/stream_item_widget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/stream_content.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/running_stream_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/edit_relay_stream_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/stream_settings_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/select_stream_type_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/create_stream_conn_info_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/start_stream_loading.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/input_remote_pwd_dialog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/stream_state_checker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/connected_info_panel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/connected_info_tag.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/connected_info_sliding_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/devices/stream_messages.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/util/conn_info_parser.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/clipboard/panel_clipboard_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/clipboard/win/panel_cp_file_stream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/clipboard/win/panel_cp_virtual_file.cpp

        ${CMAKE_CURRENT_SOURCE_DIR}/gr_guard_starter.cpp

        PARENT_SCOPE
)