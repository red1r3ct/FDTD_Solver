export const LOGIN = 'LOGIN';
export const LOGIN_SUCCESS = 'LOGIN_SUCCESS';
export const LOGIN_FAILED = 'LOGIN_FAILED';

export const LOGOUT = 'LOGOUT';
export const LOGOUT_SUCCESS = 'LOGOUT_SUCCESS';
export const LOGOUT_FAILED = 'LOGOUT_FAILED';

export const CHECK_AUTH = 'CHECK_AUTH';
export const CHECK_AUTH_SUCCESS = 'CHECK_AUTH_SUCCESS';
export const CHECK_AUTH_FAILED = 'CHECK_AUTH_FAILED';

export const checkAuth = () => ({
	type: CHECK_AUTH,
});

export const checkAuthSuccess = (user) => ({
	type: CHECK_AUTH_SUCCESS,
	payload: user,
});

export const checkAuthFailed = () => ({
	type: CHECK_AUTH_FAILED,
});

export const login = (method) => ({
	type: LOGIN,
	payload: method,
});

export const loginSuccess = (user) => ({
	type: LOGIN_SUCCESS,
	payload: user,
});

export const loginFailed = () => ({
	type: LOGIN_FAILED,
});

export const logout = () => ({
	type: LOGOUT,
});

export const logoutSuccess = () => ({
	type: LOGOUT_SUCCESS,
});

export const logoutFailed = () => ({
	type: LOGOUT_FAILED,
});
