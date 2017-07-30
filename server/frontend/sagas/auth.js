import {
	takeEvery,
	call,
	put
} from 'redux-saga/effects';
import {
	LOGIN,
	CHECK_AUTH,
	LOGOUT,
	checkAuthFailed,
	checkAuthSuccess
} from '../actions/auth';
import {checkAuth} from '../api';
import {push} from 'react-router-redux'

export function* authWatcher() {
	yield takeEvery(LOGIN, loginWorker);
	yield takeEvery(CHECK_AUTH, checkAuthWorker);
	yield takeEvery(LOGOUT, logoutWorker);
}

export function* loginWorker(action) {
	window.location.replace(`/api/auth/${action.payload}`);
}

export function* checkAuthWorker() {
	const {res, err} = yield call(checkAuth);
	if (err) {
		yield put(checkAuthFailed());
		yield put(push('/auth'));
		return;
	}
	return put(checkAuthSuccess(res.user));
}

export function* logoutWorker() {
	//todo
}
