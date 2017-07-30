import {handleActions} from 'redux-actions';
import {LOGIN_SUCCESS, CHECK_AUTH_SUCCESS, LOGOUT_SUCCESS} from '../actions/auth';


const initialState = {
	username: "",
	avatarUrl: "",
	role: "",
	isAuth: false,
};

export const userReducer = handleActions({
	[LOGIN_SUCCESS]: (state, action) => ({
		username: action.payload.username,
		avatarUrl: action.payload.avatarUrl,
		role: action.payload.role,
		isAuth: true,
	}),

	[CHECK_AUTH_SUCCESS]: (state, action) => ({
		username: action.payload.username,
		avatarUrl: action.payload.avatarUrl,
		role: action.payload.role,
		isAuth: true,
	}),

	[LOGOUT_SUCCESS]: (state, action) => ({
		...initialState
	})
}, initialState);

export default userReducer;
